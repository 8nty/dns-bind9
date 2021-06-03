/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_X25_19_H
#define GENERIC_X25_19_H 1

/*!
 *  \brief Per RFC1183 */

typedef struct dns_rdata_x25 {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	unsigned char *x25;
	uint8_t x25_len;
} dns_rdata_x25_t;

#endif /* GENERIC_X25_19_H */
