/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef IN_1_PX_26_H
#define IN_1_PX_26_H 1

/*!
 *  \brief Per RFC2163 */

typedef struct dns_rdata_in_px {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint16_t preference;
	dns_name_t map822;
	dns_name_t mapx400;
} dns_rdata_in_px_t;

#endif /* IN_1_PX_26_H */
