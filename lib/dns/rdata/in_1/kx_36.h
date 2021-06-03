/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef IN_1_KX_36_H
#define IN_1_KX_36_H 1

/*!
 *  \brief Per RFC2230 */

typedef struct dns_rdata_in_kx {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint16_t preference;
	dns_name_t exchange;
} dns_rdata_in_kx_t;

#endif /* IN_1_KX_36_H */
