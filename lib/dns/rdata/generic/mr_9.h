/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_MR_9_H
#define GENERIC_MR_9_H 1

typedef struct dns_rdata_mr {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t mr;
} dns_rdata_mr_t;

#endif /* GENERIC_MR_9_H */
