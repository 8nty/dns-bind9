/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_ISDN_20_H
#define GENERIC_ISDN_20_H 1

/*!
 * \brief Per RFC1183 */

typedef struct dns_rdata_isdn {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	char *isdn;
	char *subaddress;
	uint8_t isdn_len;
	uint8_t subaddress_len;
} dns_rdata_isdn_t;

#endif /* GENERIC_ISDN_20_H */
