/*
 * Copyright (C) Internet Systems Consortium, Inc. ("ISC")
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * See the COPYRIGHT file distributed with this work for additional
 * information regarding copyright ownership.
 */

#ifndef DNS_KASP_H
#define DNS_KASP_H 1

/*****
 ***** Module Info
 *****/

/*! \file dns/kasp.h
 * \brief
 * DNSSEC Key and Signing Policy (KASP)
 *
 * A "kasp" is a DNSSEC policy, that determines how a zone should be
 * signed and maintained.
 */

#include <time.h>

#include <isc/lang.h>
#include <isc/magic.h>
#include <isc/mutex.h>
#include <isc/refcount.h>

#include <dns/types.h>

ISC_LANG_BEGINDECLS

/* Stores a KASP key */
struct dns_kasp_key {
	isc_mem_t*			mctx;

	/* Locked by themselves. */
	isc_refcount_t			references;

	/* Under owner's locking control. */
	ISC_LINK(struct dns_kasp_key)   link;

	/* Configuration */
	time_t				lifetime;
	uint32_t			algorithm;
	int				length;
	uint8_t				role;
};

/* Stores a DNSSEC policy */
struct dns_kasp {
	unsigned int			magic;
	isc_mem_t*			mctx;
	char*				name;

	/* Internals. */
	isc_mutex_t			lock;
	bool				frozen;

	/* Locked by themselves. */
	isc_refcount_t			references;

	/* Under owner's locking control. */
	ISC_LINK(struct dns_kasp)	link;

	/* Configuration: signatures */
	time_t				signatures_resign;
	time_t				signatures_refresh;
	time_t				signatures_validity;
	time_t				signatures_validity_dnskey;
	time_t				signatures_validity_denial;
	time_t				signatures_jitter;
	time_t				signatures_inception_offset;

	/* Keys */
	dns_kasp_keylist_t		keys;
	time_t				publish_safety;
	time_t				retire_safety;
	dns_ttl_t			dnskey_ttl;

	/* Zone settings */
	dns_ttl_t			zone_max_ttl;
	time_t				zone_propagation_delay;

	/* Parent settings */
	dns_ttl_t			parent_ds_ttl;
	time_t				parent_propagation_delay;
	time_t				parent_registration_delay;

	// TODO: The rest of the KASP configuration
};

#define DNS_KASP_MAGIC			ISC_MAGIC('K','A','S','P')
#define DNS_KASP_VALID(kasp)		ISC_MAGIC_VALID(kasp, DNS_KASP_MAGIC)

/* Defaults */
#define DNS_KASP_SIG_RESIGN		(3600)
#define DNS_KASP_SIG_REFRESH		(86400*5)
#define DNS_KASP_SIG_VALIDITY		(86400*14)
#define DNS_KASP_SIG_VALIDITY_DNSKEY	(86400*14)
#define DNS_KASP_SIG_VALIDITY_DENIAL	(86400*14)
#define DNS_KASP_SIG_JITTER		(0)
#define DNS_KASP_SIG_INCEPTION_OFFSET	(3600)
#define DNS_KASP_DNSKEY_TTL		(3600)
#define DNS_KASP_DS_TTL			(3600)
#define DNS_KASP_PUBLISH_SAFETY		(3600)
#define DNS_KASP_RETIRE_SAFETY		(3600)
#define DNS_KASP_ZONE_MAXTTL		(86400)
#define DNS_KASP_ZONE_PROPDELAY		(300)
#define DNS_KASP_PARENT_PROPDELAY	(3600)
#define DNS_KASP_PARENT_REGDELAY	(86400)

/* Key roles */
#define DNS_KASP_KEY_ROLE_KSK		0x01
#define DNS_KASP_KEY_ROLE_ZSK		0x02

isc_result_t
dns_kasp_create(isc_mem_t *mctx, const char* name, dns_kasp_t **kaspp);
/*%<
 * Create a KASP.
 *
 * Requires:
 *
 *\li  'mctx' is a valid memory context.
 *
 *\li  'name' is a valid C string.
 *
 *\li  kaspp != NULL && *kaspp == NULL
 *
 * Returns:
 *
 *\li  #ISC_R_SUCCESS
 *\li  #ISC_R_NOMEMORY
 *
 *\li  Other errors are possible.
 */

void
dns_kasp_attach(dns_kasp_t *source, dns_kasp_t **targetp);
/*%<
 * Attach '*targetp' to 'source'.
 *
 * Requires:
 *
 *\li   'source' is a valid, frozen kasp.
 *
 *\li   'targetp' points to a NULL dns_kasp_t *.
 *
 * Ensures:
 *
 *\li   *targetp is attached to source.
 *
 *\li   While *targetp is attached, the kasp will not shut down.
 */

void
dns_kasp_detach(dns_kasp_t **kaspp);
/*%<
 * Detach KASP.
 *
 * Requires:
 *
 *\li   'kaspp' points to a valid dns_kasp_t *
 *
 * Ensures:
 *
 *\li   *kaspp is NULL.
 */

void
dns_kasp_freeze(dns_kasp_t *kasp);
/*%<
 * Freeze kasp.  No changes can be made to kasp configuration while frozen.
 *
 * Requires:
 *
 *\li   'kasp' is a valid, unfrozen kasp.
 *
 * Ensures:
 *
 *\li   'kasp' is frozen.
 */

void
dns_kasp_thaw(dns_kasp_t *kasp);
/*%<
 * Thaw kasp.
 *
 * Requires:
 *
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Ensures:
 *
 *\li   'kasp' is no longer frozen.
 */

const char*
dns_kasp_getname(dns_kasp_t *kasp);
/*%<
 * Get kasp name.
 *
 * Requires:
 *
 *\li   'kasp' is a valid kasp.
 *
 * Returns:
 *
 *\li   name of 'kasp'.
 */

time_t
dns_kasp_signdelay(dns_kasp_t *kasp);
/*%<
 * Get the delay that is needed to ensure that all existing RRsets have been
 * re-signed with a successor key.  This is the signature validity minus the
 * signature refresh time (that indicates how far before signature expiry an
 * RRSIG should be refreshed).
 *
 * Requires:
 *
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Returns:
 *
 *\li   signature refresh interval.
 */

time_t
dns_kasp_siginceptionoffset(dns_kasp_t *kasp);
/*%<
 * Get signature inception offset.
 *
 * Requires:
 *
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Returns:
 *
 *\li   signature inception offset.
 */

time_t
dns_kasp_sigjitter(dns_kasp_t *kasp);
/*%<
 * Get signature jitter.
 *
 * Requires:
 *
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Returns:
 *
 *\li   signature jitter.
 */

time_t
dns_kasp_sigrefresh(dns_kasp_t *kasp);
/*%<
 * Get signature refresh interval.
 *
 * Requires:
 *
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Returns:
 *
 *\li   signature refresh interval.
 */

time_t
dns_kasp_sigresign(dns_kasp_t *kasp);
/*%<
 * Get signature resign interval.
 *
 * Requires:
 *
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Returns:
 *
 *\li   signature resign interval.
 */

time_t
dns_kasp_sigvalidity(dns_kasp_t *kasp);
time_t
dns_kasp_sigvalidity_dnskey(dns_kasp_t *kasp);
time_t
dns_kasp_sigvalidity_denial(dns_kasp_t *kasp);
/*%<
 * Get signature validity.
 *
 * Requires:
 *
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Returns:
 *
 *\li   signature validity.
 */

dns_ttl_t
dns_kasp_dnskeyttl(dns_kasp_t *kasp);
/*%<
 * Get dnskey ttl.
 *
 * Requires:
 *
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Returns:
 *
 *\li   DNSKEY TTL.
 */

time_t
dns_kasp_publishsafety(dns_kasp_t *kasp);
/*%<
 * Get publish safety interval.
 *
 * Requires:
 *
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Returns:
 *
 *\li   Publish safety interval.
 */

time_t
dns_kasp_retiresafety(dns_kasp_t *kasp);
/*%<
 * Get retire safety interval.
 *
 * Requires:
 *
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Returns:
 *
 *\li   Retire safety interval.
 */

dns_ttl_t
dns_kasp_zonemaxttl(dns_kasp_t *kasp);
/*%<
 * Get maximum zone TTL.
 *
 * Requires:
 *
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Returns:
 *
 *\li   Maximum zone TTL.
 */

time_t
dns_kasp_zonepropagationdelay(dns_kasp_t *kasp);
/*%<
 * Get zone propagation delay.
 *
 * Requires:
 *
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Returns:
 *
 *\li   Zone propagation delay.
 */

dns_ttl_t
dns_kasp_dsttl(dns_kasp_t *kasp);
/*%<
 * Get DS TTL (should match that of the parent DS record).
 *
 * Requires:
 *
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Returns:
 *
 *\li   Expected parent DS TTL.
 */

time_t
dns_kasp_parentpropagationdelay(dns_kasp_t *kasp);
/*%<
 * Get parent zone propagation delay.
 *
 * Requires:
 *
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Returns:
 *
 *\li   Parent zone propagation delay.
 */

time_t
dns_kasp_parentregistrationdelay(dns_kasp_t *kasp);
/*%<
 * Get parent registration delay for submitting new DS.
 *
 * Requires:
 *
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Returns:
 *
 *\li   Parent registration delay.
 */

isc_result_t
dns_kasplist_find(dns_kasplist_t *list, const char *name, dns_kasp_t **kaspp);
/*%<
 * Search for a kasp with name 'name' in 'list'.
 * If found, '*kaspp' is (strongly) attached to it.
 *
 * Requires:
 *
 *\li   'kaspp' points to a NULL dns_kasp_t *.
 *
 * Returns:
 *
 *\li   #ISC_R_SUCCESS          A matching kasp was found.
 *\li   #ISC_R_NOTFOUND         No matching kasp was found.
 */

isc_result_t
dns_kasp_key_create(isc_mem_t* mctx, dns_kasp_key_t **keyp);
/*%<
 * Create a key inside a KASP.
 *
 * Requires:
 *
 *\li  'mctx' is a valid memory context.
 *
 *\li  keyp != NULL && *keyp == NULL
 *
 * Returns:
 *
 *\li  #ISC_R_SUCCESS
 *\li  #ISC_R_NOMEMORY
 *
 *\li  Other errors are possible.
 */

void
dns_kasp_key_destroy(dns_kasp_key_t* key);
/*%<
 * Destroy a KASP key.
 *
 * Requires:
 *
 *\li  key != NULL
 */

uint32_t
dns_kasp_key_algorithm(dns_kasp_key_t *key);
/*%<
 * Get the key algorithm.
 *
 * Requires:
 *
 *\li  key != NULL
 *
 * Returns:
 *
 *\li  Key algorithm.
 */

unsigned int
dns_kasp_key_size(dns_kasp_key_t *key);
/*%<
 * Get the key size.
 *
 * Requires:
 *
 *\li  key != NULL
 *
 * Returns:
 *
 *\li  Configured key size, or default key size for key algorithm if no size
 *     configured.
 */

time_t
dns_kasp_key_lifetime(dns_kasp_key_t *key);
/*%<
 * The lifetime of this key (how long may this key be active?)
 *
 * Requires:
 *
 *\li  key != NULL
 *
 * Returns:
 *
 *\li  Lifetime of key.
 *
 */

bool
dns_kasp_key_ksk(dns_kasp_key_t *key);
/*%<
 * Does this key act as a KSK?
 *
 * Requires:
 *
 *\li  key != NULL
 *
 * Returns:
 *
 *\li  True, if the key role has DNS_KASP_KEY_ROLE_KSK set.
 *\li  False, otherwise.
 *
 */

bool
dns_kasp_key_zsk(dns_kasp_key_t *key);
/*%<
 * Does this key act as a ZSK?
 *
 * Requires:
 *
 *\li  key != NULL
 *
 * Returns:
 *
 *\li  True, if the key role has DNS_KASP_KEY_ROLE_ZSK set.
 *\li  False, otherwise.
 *
 */

ISC_LANG_ENDDECLS

#endif /* DNS_KASP_H */

