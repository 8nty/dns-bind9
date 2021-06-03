/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_CERT_37_H
#define GENERIC_CERT_37_H 1

/*% RFC2538 */
typedef struct dns_rdata_cert {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint16_t type;
	uint16_t key_tag;
	uint8_t algorithm;
	uint16_t length;
	unsigned char *certificate;
} dns_rdata_cert_t;

#endif /* GENERIC_CERT_37_H */
