/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_DOA_259_H
#define GENERIC_DOA_259_H 1

typedef struct dns_rdata_doa {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	unsigned char *mediatype;
	unsigned char *data;
	uint32_t enterprise;
	uint32_t type;
	uint16_t data_len;
	uint8_t location;
	uint8_t mediatype_len;
} dns_rdata_doa_t;

#endif /* GENERIC_DOA_259_H */
