/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_NAPTR_35_H
#define GENERIC_NAPTR_35_H 1

/*!
 *  \brief Per RFC2915 */

typedef struct dns_rdata_naptr {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint16_t order;
	uint16_t preference;
	char *flags;
	uint8_t flags_len;
	char *service;
	uint8_t service_len;
	char *regexp;
	uint8_t regexp_len;
	dns_name_t replacement;
} dns_rdata_naptr_t;

#endif /* GENERIC_NAPTR_35_H */
