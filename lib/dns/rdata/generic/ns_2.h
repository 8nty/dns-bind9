/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_NS_2_H
#define GENERIC_NS_2_H 1

typedef struct dns_rdata_ns {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t name;
} dns_rdata_ns_t;

#endif /* GENERIC_NS_2_H */
