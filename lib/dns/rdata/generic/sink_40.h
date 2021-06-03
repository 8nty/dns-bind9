/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_SINK_40_H
#define GENERIC_SINK_40_H 1

typedef struct dns_rdata_sink_t {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint8_t meaning;
	uint8_t coding;
	uint8_t subcoding;
	uint16_t datalen;
	unsigned char *data;
} dns_rdata_sink_t;

#endif /* GENERIC_SINK_40_H */
