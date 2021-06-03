/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_PTR_12_H
#define GENERIC_PTR_12_H 1

typedef struct dns_rdata_ptr {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t ptr;
} dns_rdata_ptr_t;

#endif /* GENERIC_PTR_12_H */
