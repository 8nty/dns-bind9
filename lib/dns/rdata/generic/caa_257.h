/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_CAA_257_H
#define GENERIC_CAA_257_H 1

typedef struct dns_rdata_caa {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint8_t flags;
	unsigned char *tag;
	uint8_t tag_len;
	unsigned char *value;
	uint16_t value_len;
} dns_rdata_caa_t;

#endif /* GENERIC_CAA_257_H */
