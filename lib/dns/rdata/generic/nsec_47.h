/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_NSEC_47_H
#define GENERIC_NSEC_47_H 1

/*!
 * \brief Per RFC 3845 */

typedef struct dns_rdata_nsec {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t next;
	unsigned char *typebits;
	uint16_t len;
} dns_rdata_nsec_t;

#endif /* GENERIC_NSEC_47_H */
