/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_NSEC3PARAM_51_H
#define GENERIC_NSEC3PARAM_51_H 1

/*!
 * \brief Per RFC 5155 */

#include <isc/iterated_hash.h>

typedef struct dns_rdata_nsec3param {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_hash_t hash;
	unsigned char flags; /* DNS_NSEC3FLAG_* */
	dns_iterations_t iterations;
	unsigned char salt_length;
	unsigned char *salt;
} dns_rdata_nsec3param_t;

#endif /* GENERIC_NSEC3PARAM_51_H */
