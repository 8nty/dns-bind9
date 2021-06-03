/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ANY_255_TSIG_250_H
#define ANY_255_TSIG_250_H 1

/*% RFC2845 */
typedef struct dns_rdata_any_tsig {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t algorithm;
	uint64_t timesigned;
	uint16_t fudge;
	uint16_t siglen;
	unsigned char *signature;
	uint16_t originalid;
	uint16_t error;
	uint16_t otherlen;
	unsigned char *other;
} dns_rdata_any_tsig_t;

#endif /* ANY_255_TSIG_250_H */
