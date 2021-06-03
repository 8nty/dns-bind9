/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_ZONEMD_63_H
#define GENERIC_ZONEMD_63_H 1

/* Known digest type(s). */
#define DNS_ZONEMD_DIGEST_SHA384 (1)
#define DNS_ZONEMD_DIGEST_SHA512 (2)

/*
 *  \brief per RFC 8976
 */
typedef struct dns_rdata_zonemd {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint32_t serial;
	uint8_t scheme;
	uint8_t digest_type;
	unsigned char *digest;
	uint16_t length;
} dns_rdata_zonemd_t;

#endif /* GENERIC_ZONEMD_63_H */
