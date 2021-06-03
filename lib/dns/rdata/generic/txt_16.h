/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_TXT_16_H
#define GENERIC_TXT_16_H 1

typedef struct dns_rdata_txt_string {
	uint8_t length;
	unsigned char *data;
} dns_rdata_txt_string_t;

typedef struct dns_rdata_txt {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	unsigned char *txt;
	uint16_t txt_len;
	/* private */
	uint16_t offset;
} dns_rdata_txt_t;

/*
 * ISC_LANG_BEGINDECLS and ISC_LANG_ENDDECLS are already done
 * via rdatastructpre.h and rdatastructsuf.h.
 */

isc_result_t
dns_rdata_txt_first(dns_rdata_txt_t *);

isc_result_t
dns_rdata_txt_next(dns_rdata_txt_t *);

isc_result_t
dns_rdata_txt_current(dns_rdata_txt_t *, dns_rdata_txt_string_t *);

#endif /* GENERIC_TXT_16_H */
