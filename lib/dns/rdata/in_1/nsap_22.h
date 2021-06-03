/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef IN_1_NSAP_22_H
#define IN_1_NSAP_22_H 1

/*!
 *  \brief Per RFC1706 */

typedef struct dns_rdata_in_nsap {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	unsigned char *nsap;
	uint16_t nsap_len;
} dns_rdata_in_nsap_t;

#endif /* IN_1_NSAP_22_H */
