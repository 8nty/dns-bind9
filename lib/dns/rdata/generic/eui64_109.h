/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_EUI64_109_H
#define GENERIC_EUI64_109_H 1

typedef struct dns_rdata_eui64 {
	dns_rdatacommon_t common;
	unsigned char eui64[8];
} dns_rdata_eui64_t;

#endif /* GENERIC_EUI64_10k_H */
