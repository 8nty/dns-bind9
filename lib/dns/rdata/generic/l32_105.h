/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_L32_105_H
#define GENERIC_L32_105_H 1

typedef struct dns_rdata_l32 {
	dns_rdatacommon_t common;
	uint16_t pref;
	struct in_addr l32;
} dns_rdata_l32_t;

#endif /* GENERIC_L32_105_H */
