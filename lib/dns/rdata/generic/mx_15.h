/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_MX_15_H
#define GENERIC_MX_15_H 1

typedef struct dns_rdata_mx {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint16_t pref;
	dns_name_t mx;
} dns_rdata_mx_t;

#endif /* GENERIC_MX_15_H */
