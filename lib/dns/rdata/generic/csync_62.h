/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_CSYNC_62_H
#define GENERIC_CSYNC_62_H 1

/*!
 * \brief Per RFC 7477
 */

typedef struct dns_rdata_csync {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint32_t serial;
	uint16_t flags;
	unsigned char *typebits;
	uint16_t len;
} dns_rdata_csync_t;

#endif /* GENERIC_CSYNC_62_H */
