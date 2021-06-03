/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/*!
 *  \brief Per RFC 4255 */

#ifndef GENERIC_SSHFP_44_H
#define GENERIC_SSHFP_44_H 1

typedef struct dns_rdata_sshfp {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint8_t algorithm;
	uint8_t digest_type;
	uint16_t length;
	unsigned char *digest;
} dns_rdata_sshfp_t;

#endif /* GENERIC_SSHFP_44_H */
