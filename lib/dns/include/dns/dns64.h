/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef DNS_DNS64_H
#define DNS_DNS64_H 1

#include <stdbool.h>

#include <isc/lang.h>

#include <dns/types.h>

ISC_LANG_BEGINDECLS

/*
 * dns_dns64_create() flags.
 */
#define DNS_DNS64_RECURSIVE_ONLY          \
	0x01 /* If set then this record   \
	      * only applies to recursive \
	      * queries.                  \
	      */
#define DNS_DNS64_BREAK_DNSSEC            \
	0x02 /* If set then still perform \
	      * DNSSEC synthesis even     \
	      * though the result would   \
	      * fail validation.          \
	      */

/*
 * dns_dns64_aaaaok() and dns_dns64_aaaafroma() flags.
 */
#define DNS_DNS64_RECURSIVE 0x01 /* Recursive query. */
#define DNS_DNS64_DNSSEC    0x02 /* DNSSEC sensitive query. */

isc_result_t
dns_dns64_create(isc_mem_t *mctx, const isc_netaddr_t *prefix,
		 unsigned int prefixlen, const isc_netaddr_t *suffix,
		 dns_acl_t *client, dns_acl_t *mapped, dns_acl_t *excluded,
		 unsigned int flags, dns_dns64_t **dns64);
/*
 * Create a dns64 record which is used to identify the set of clients
 * it applies to and how to perform the DNS64 synthesis.
 *
 * 'prefix' and 'prefixlen' defined the leading bits of the AAAA records
 * to be synthesised.  'suffix' defines the bits after the A records bits.
 * If suffix is NULL zeros will be used for these bits.  'client' defines
 * for which clients this record applies.  If 'client' is NULL then all
 * clients apply.  'mapped' defines which A records are candidated for
 * mapping.  If 'mapped' is NULL then all A records will be mapped.
 * 'excluded' defines which AAAA are to be treated as non-existent for the
 * purposed of determining whether to perform synthesis.  If 'excluded' is
 * NULL then no AAAA records prevent synthesis.
 *
 * If DNS_DNS64_RECURSIVE_ONLY is set then the record will only match if
 * DNS_DNS64_RECURSIVE is set when calling  dns_dns64_aaaaok() and
 * dns_dns64_aaaafroma().
 *
 * If DNS_DNS64_BREAK_DNSSEC is set then the record will still apply if
 * DNS_DNS64_DNSSEC is set when calling  dns_dns64_aaaaok() and
 * dns_dns64_aaaafroma() otherwise the record will be ignored.
 *
 * Requires:
 *      'mctx'          to be valid.
 *      'prefix'        to be valid and the address family to AF_INET6.
 *      'prefixlen'     to be one of 32, 40, 48, 56, 72 and 96.
 *                      the bits not covered by prefixlen in prefix to
 *                      be zero.
 *      'suffix'        to be NULL or the address family be set to AF_INET6
 *                      and the leading 'prefixlen' + 32 bits of the 'suffix'
 *                      to be zero.  If 'prefixlen' is 40, 48 or 56 then the
 *                      the leading 'prefixlen' + 40 bits of 'suffix' must be
 *                      zero.
 *	'client'	to be NULL or a valid acl.
 *	'mapped'	to be NULL or a valid acl.
 *	'excluded'	to be NULL or a valid acl.
 *
 * Returns:
 *	ISC_R_SUCCESS
 *	ISC_R_NOMEMORY
 */

void
dns_dns64_destroy(dns_dns64_t **dns64p);
/*
 * Destroys a dns64 record.
 *
 * Requires the record to not be linked.
 */

isc_result_t
dns_dns64_aaaafroma(const dns_dns64_t *dns64, const isc_netaddr_t *reqaddr,
		    const dns_name_t *reqsigner, const dns_aclenv_t *env,
		    unsigned int flags, unsigned char *a, unsigned char *aaaa);
/*
 * dns_dns64_aaaafroma() determines whether to perform a DNS64 address
 * synthesis from 'a' based on 'dns64', 'reqaddr', 'reqsigner', 'env',
 * 'flags' and 'aaaa'.  If synthesis is performed then the result is
 * written to '*aaaa'.
 *
 * The synthesised address will be of the form:
 *
 *	 <prefix bits><a bits><suffix bits>
 *
 * If <a bits> straddle bits 64-71 of the AAAA record, then 8 zero bits will
 * be inserted at bits 64-71.
 *
 * Requires:
 *	'dns64'		to be valid.
 *	'reqaddr'	to be valid.
 *	'reqsigner'	to be NULL or valid.
 *	'env'		to be valid.
 *	'a'		to point to a IPv4 address in network order.
 *	'aaaa'		to point to a IPv6 address buffer in network order.
 *
 * Returns:
 *	ISC_R_SUCCESS		if synthesis was performed.
 *	DNS_R_DISALLOWED	if there is no match.
 */

dns_dns64_t *
dns_dns64_next(dns_dns64_t *dns64);
/*
 * Return the next dns64 record in the list.
 */

void
dns_dns64_append(dns_dns64list_t *list, dns_dns64_t *dns64);
/*
 * Append the dns64 record to the list.
 */

void
dns_dns64_unlink(dns_dns64list_t *list, dns_dns64_t *dns64);
/*
 * Unlink the dns64 record from the list.
 */

bool
dns_dns64_aaaaok(const dns_dns64_t *dns64, const isc_netaddr_t *reqaddr,
		 const dns_name_t *reqsigner, const dns_aclenv_t *env,
		 unsigned int flags, dns_rdataset_t *rdataset, bool *aaaaok,
		 size_t aaaaoklen);
/*
 * Determine if there are any non-excluded AAAA records in from the
 * matching dns64 records in the list starting at 'dns64'.  If there
 * is a non-excluded address return true.  If all addresses are
 * excluded in the matched records return false.   If no records
 * match then return true.
 *
 * If aaaaok is defined then dns_dns64_aaaaok() return a array of which
 * addresses in 'rdataset' were deemed to not be exclude by any matching
 * record.  If there are no matching records then all entries are set
 * to true.
 *
 * Requires
 * 	'rdataset'	to be valid and to be for type AAAA and class IN.
 *	'aaaaoklen'	must match the number of records in 'rdataset'
 *			if 'aaaaok' in non NULL.
 */

isc_result_t
dns_dns64_findprefix(dns_rdataset_t *rdataset, isc_netprefix_t *prefix,
		     size_t *len);
/*
 * Look through 'rdataset' for AAAA pairs which define encoded DNS64 prefixes.
 * 'len' should be set to the number of entries in 'prefix' and returns
 * the number of prefixes discovered.  This may be bigger than those that
 * can fit in 'prefix'.
 *
 * Requires
 * 	'rdataset'	to be valid and to be for type AAAA and class IN.
 *	'prefix'	to be non NULL.
 *	'len'		to be non NULL and non zero.
 *
 * Returns
 * 	ISC_R_SUCCESS
 *	ISC_R_NOSPACE	if there are more prefixes discovered than can fit
 *			into 'prefix'.
 *	ISC_R_NOTFOUND	no prefixes where found.
 */

ISC_LANG_ENDDECLS

#endif /* DNS_DNS64_H */
