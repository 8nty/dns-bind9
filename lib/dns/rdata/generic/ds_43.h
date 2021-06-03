/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_DS_43_H
#define GENERIC_DS_43_H 1

/*!
 *  \brief per draft-ietf-dnsext-delegation-signer-05.txt */
typedef struct dns_rdata_ds {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint16_t key_tag;
	dns_secalg_t algorithm;
	dns_dsdigest_t digest_type;
	uint16_t length;
	unsigned char *digest;
} dns_rdata_ds_t;

#endif /* GENERIC_DS_43_H */
