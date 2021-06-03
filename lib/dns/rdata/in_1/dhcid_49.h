/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef IN_1_DHCID_49_H
#define IN_1_DHCID_49_H 1

typedef struct dns_rdata_in_dhcid {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	unsigned char *dhcid;
	unsigned int length;
} dns_rdata_in_dhcid_t;

#endif /* IN_1_DHCID_49_H */
