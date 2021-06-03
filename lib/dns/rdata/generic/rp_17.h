/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_RP_17_H
#define GENERIC_RP_17_H 1

/*!
 *  \brief Per RFC1183 */

typedef struct dns_rdata_rp {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t mail;
	dns_name_t text;
} dns_rdata_rp_t;

#endif /* GENERIC_RP_17_H */
