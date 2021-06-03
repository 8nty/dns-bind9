/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef IN_1_NIMLOC_32_H
#define IN_1_NIMLOC_32_H 1

/*!
 *  \brief http://ana-3.lcs.mit.edu/~jnc/nimrod/dns.txt
 */

typedef struct dns_rdata_in_nimloc {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	unsigned char *nimloc;
	uint16_t nimloc_len;
} dns_rdata_in_nimloc_t;

#endif /* IN_1_NIMLOC_32_H */
