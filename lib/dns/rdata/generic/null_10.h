/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_NULL_10_H
#define GENERIC_NULL_10_H 1

typedef struct dns_rdata_null {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint16_t length;
	unsigned char *data;
} dns_rdata_null_t;

#endif /* GENERIC_NULL_10_H */
