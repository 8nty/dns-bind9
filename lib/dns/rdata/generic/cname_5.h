/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_CNAME_5_H
#define GENERIC_CNAME_5_H 1

typedef struct dns_rdata_cname {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t cname;
} dns_rdata_cname_t;

#endif /* GENERIC_CNAME_5_H */
