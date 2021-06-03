/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_MB_7_H
#define GENERIC_MB_7_H 1

typedef struct dns_rdata_mb {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t mb;
} dns_rdata_mb_t;

#endif /* GENERIC_MB_7_H */
