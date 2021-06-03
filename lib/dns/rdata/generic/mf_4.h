/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_MF_4_H
#define GENERIC_MF_4_H 1

typedef struct dns_rdata_mf {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t mf;
} dns_rdata_mf_t;

#endif /* GENERIC_MF_4_H */
