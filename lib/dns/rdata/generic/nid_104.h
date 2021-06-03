/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_NID_104_H
#define GENERIC_NID_104_H 1

typedef struct dns_rdata_nid {
	dns_rdatacommon_t common;
	uint16_t pref;
	unsigned char nid[8];
} dns_rdata_nid_t;

#endif /* GENERIC_NID_104_H */
