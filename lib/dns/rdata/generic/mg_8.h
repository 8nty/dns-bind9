/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_MG_8_H
#define GENERIC_MG_8_H 1

typedef struct dns_rdata_mg {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t mg;
} dns_rdata_mg_t;

#endif /* GENERIC_MG_8_H */
