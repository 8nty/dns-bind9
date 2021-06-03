/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_EUI48_108_H
#define GENERIC_EUI48_108_H 1

typedef struct dns_rdata_eui48 {
	dns_rdatacommon_t common;
	unsigned char eui48[6];
} dns_rdata_eui48_t;

#endif /* GENERIC_EUI48_10k_H */
