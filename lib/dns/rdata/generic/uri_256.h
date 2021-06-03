/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_URI_256_H
#define GENERIC_URI_256_H 1

typedef struct dns_rdata_uri {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint16_t priority;
	uint16_t weight;
	unsigned char *target;
	uint16_t tgt_len;
} dns_rdata_uri_t;

#endif /* GENERIC_URI_256_H */
