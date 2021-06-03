/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef IN_1_ATMA_22_H
#define IN_1_ATMA_22_H 1

/*!
 *  \brief Per RFC1706 */

typedef struct dns_rdata_in_atma {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	unsigned char format;
	unsigned char *atma;
	uint16_t atma_len;
} dns_rdata_in_atma_t;

#endif /* IN_1_ATMA_22_H */
