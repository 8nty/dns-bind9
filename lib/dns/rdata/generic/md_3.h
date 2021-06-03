/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_MD_3_H
#define GENERIC_MD_3_H 1

typedef struct dns_rdata_md {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t md;
} dns_rdata_md_t;

#endif /* GENERIC_MD_3_H */
