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
	time_t				dnskey_publish_safety;
	time_t				dnskey_retire_safety;
	uint32_t			dnskey_ttl;


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
#define DNS_KASP_KEY_TTL		(3600)
#define DNS_KASP_KEY_PUBLISH_SAFETY	(300)
#define DNS_KASP_KEY_RETIRE_SAFETY	(300)
#define DNS_KASP_ZONE_MAXTTL		(86400)

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
 *\li   'kasp' is a valid, frozen kasp.
 *
 * Returns:
 *
 *\li   name of 'kasp'.
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
 *\li  'key' is a valid KASP key.
 *
 *\li  kasp != NULL && key != NULL
 */

ISC_LANG_ENDDECLS

#endif /* DNS_KASP_H */

