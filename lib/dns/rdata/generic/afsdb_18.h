/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_AFSDB_18_H
#define GENERIC_AFSDB_18_H 1

/*!
 *  \brief Per RFC1183 */

typedef struct dns_rdata_afsdb {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint16_t subtype;
	dns_name_t server;
} dns_rdata_afsdb_t;

#endif /* GENERIC_AFSDB_18_H */
