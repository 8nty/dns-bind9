/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef IN_1_A_1_H
#define IN_1_A_1_H 1

typedef struct dns_rdata_in_a {
	dns_rdatacommon_t common;
	struct in_addr in_addr;
} dns_rdata_in_a_t;

#endif /* IN_1_A_1_H */
