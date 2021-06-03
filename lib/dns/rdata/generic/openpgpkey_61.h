/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_OPENPGPKEY_61_H
#define GENERIC_OPENPGPKEY_61_H 1

typedef struct dns_rdata_openpgpkey {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint16_t length;
	unsigned char *keyring;
} dns_rdata_openpgpkey_t;

#endif /* GENERIC_OPENPGPKEY_61_H */
