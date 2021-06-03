/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef HS_4_A_1_H
#define HS_4_A_1_H 1

typedef struct dns_rdata_hs_a {
	dns_rdatacommon_t common;
	struct in_addr in_addr;
} dns_rdata_hs_a_t;

#endif /* HS_4_A_1_H */
