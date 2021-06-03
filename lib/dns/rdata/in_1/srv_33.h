/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef IN_1_SRV_33_H
#define IN_1_SRV_33_H 1

/*!
 *  \brief Per RFC2782 */

typedef struct dns_rdata_in_srv {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint16_t priority;
	uint16_t weight;
	uint16_t port;
	dns_name_t target;
} dns_rdata_in_srv_t;

#endif /* IN_1_SRV_33_H */
