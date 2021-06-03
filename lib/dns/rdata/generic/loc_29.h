/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_LOC_29_H
#define GENERIC_LOC_29_H 1

/*!
 * \brief Per RFC1876 */

typedef struct dns_rdata_loc_0 {
	uint8_t version; /* must be first and zero */
	uint8_t size;
	uint8_t horizontal;
	uint8_t vertical;
	uint32_t latitude;
	uint32_t longitude;
	uint32_t altitude;
} dns_rdata_loc_0_t;

typedef struct dns_rdata_loc {
	dns_rdatacommon_t common;
	union {
		dns_rdata_loc_0_t v0;
	} v;
} dns_rdata_loc_t;

#endif /* GENERIC_LOC_29_H */
