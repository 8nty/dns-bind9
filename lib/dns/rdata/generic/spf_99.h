/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_SPF_99_H
#define GENERIC_SPF_99_H 1

typedef struct dns_rdata_spf_string {
	uint8_t length;
	unsigned char *data;
} dns_rdata_spf_string_t;

typedef struct dns_rdata_spf {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	unsigned char *txt;
	uint16_t txt_len;
	/* private */
	uint16_t offset;
} dns_rdata_spf_t;

/*
 * ISC_LANG_BEGINDECLS and ISC_LANG_ENDDECLS are already done
 * via rdatastructpre.h and rdatastructsuf.h.
 */
#endif /* GENERIC_SPF_99_H */
