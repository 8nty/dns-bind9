/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef IN_1_WKS_11_H
#define IN_1_WKS_11_H 1

typedef struct dns_rdata_in_wks {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	struct in_addr in_addr;
	uint16_t protocol;
	unsigned char *map;
	uint16_t map_len;
} dns_rdata_in_wks_t;

#endif /* IN_1_WKS_11_H */
