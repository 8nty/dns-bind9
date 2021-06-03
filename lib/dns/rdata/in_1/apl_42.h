/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef IN_1_APL_42_H
#define IN_1_APL_42_H 1

typedef struct dns_rdata_apl_ent {
	bool negative;
	uint16_t family;
	uint8_t prefix;
	uint8_t length;
	unsigned char *data;
} dns_rdata_apl_ent_t;

typedef struct dns_rdata_in_apl {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	/* type & class specific elements */
	unsigned char *apl;
	uint16_t apl_len;
	/* private */
	uint16_t offset;
} dns_rdata_in_apl_t;

/*
 * ISC_LANG_BEGINDECLS and ISC_LANG_ENDDECLS are already done
 * via rdatastructpre.h and rdatastructsuf.h.
 */

isc_result_t
dns_rdata_apl_first(dns_rdata_in_apl_t *);

isc_result_t
dns_rdata_apl_next(dns_rdata_in_apl_t *);

isc_result_t
dns_rdata_apl_current(dns_rdata_in_apl_t *, dns_rdata_apl_ent_t *);

unsigned int
dns_rdata_apl_count(const dns_rdata_in_apl_t *apl);

#endif /* IN_1_APL_42_H */
