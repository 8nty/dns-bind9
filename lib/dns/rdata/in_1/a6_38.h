/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef IN_1_A6_38_H
#define IN_1_A6_38_H 1

/*!
 *  \brief Per RFC2874 */

typedef struct dns_rdata_in_a6 {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t prefix;
	uint8_t prefixlen;
	struct in6_addr in6_addr;
} dns_rdata_in_a6_t;

#endif /* IN_1_A6_38_H */
