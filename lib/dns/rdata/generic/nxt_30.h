/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_NXT_30_H
#define GENERIC_NXT_30_H 1

/*!
 *  \brief RFC2535 */

typedef struct dns_rdata_nxt {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t next;
	unsigned char *typebits;
	uint16_t len;
} dns_rdata_nxt_t;

#endif /* GENERIC_NXT_30_H */
