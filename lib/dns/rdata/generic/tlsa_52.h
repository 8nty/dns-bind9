/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_TLSA_52_H
#define GENERIC_TLSA_52_H 1

/*!
 *  \brief per rfc6698.txt
 */
typedef struct dns_rdata_tlsa {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint8_t usage;
	uint8_t selector;
	uint8_t match;
	uint16_t length;
	unsigned char *data;
} dns_rdata_tlsa_t;

#endif /* GENERIC_TLSA_52_H */
