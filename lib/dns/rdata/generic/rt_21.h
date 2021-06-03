/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_RT_21_H
#define GENERIC_RT_21_H 1

/*!
 *  \brief Per RFC1183 */

typedef struct dns_rdata_rt {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint16_t preference;
	dns_name_t host;
} dns_rdata_rt_t;

#endif /* GENERIC_RT_21_H */
