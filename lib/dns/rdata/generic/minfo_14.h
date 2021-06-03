/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_MINFO_14_H
#define GENERIC_MINFO_14_H 1

typedef struct dns_rdata_minfo {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t rmailbox;
	dns_name_t emailbox;
} dns_rdata_minfo_t;

#endif /* GENERIC_MINFO_14_H */
