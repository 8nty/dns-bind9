/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef IN_1_AAAA_28_H
#define IN_1_AAAA_28_H 1

/*!
 *  \brief Per RFC1886 */

typedef struct dns_rdata_in_aaaa {
	dns_rdatacommon_t common;
	struct in6_addr in6_addr;
} dns_rdata_in_aaaa_t;

#endif /* IN_1_AAAA_28_H */
