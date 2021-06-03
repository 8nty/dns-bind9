/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_HASH_H
#define ISC_HASH_H 1

#include <inttypes.h>
#include <stdbool.h>

#include "isc/lang.h"
#include "isc/types.h"

/***
 *** Functions
 ***/
ISC_LANG_BEGINDECLS

const void *
isc_hash_get_initializer(void);

void
isc_hash_set_initializer(const void *initializer);

#define isc_hash_function isc_hash64

uint32_t
isc_hash32(const void *data, const size_t length, const bool case_sensitive);
uint64_t
isc_hash64(const void *data, const size_t length, const bool case_sensitive);
/*!<
 * \brief Calculate a hash over data.
 *
 * This hash function is useful for hashtables. The hash function is
 * opaque and not important to the caller. The returned hash values are
 * non-deterministic and will have different mapping every time a
 * process using this library is run, but will have uniform
 * distribution.
 *
 * isc_hash_32/64() calculates the hash from start to end over the
 * input data.
 *
 * 'data' is the data to be hashed.
 *
 * 'length' is the size of the data to be hashed.
 *
 * 'case_sensitive' specifies whether the hash key should be treated as
 * case_sensitive values.  It should typically be false if the hash key
 * is a DNS name.
 *
 * Returns:
 * \li 32 or 64-bit hash value
 */

ISC_LANG_ENDDECLS

#endif /* ISC_HASH_H */
