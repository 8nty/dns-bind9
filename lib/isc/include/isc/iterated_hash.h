/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

#include <isc/lang.h>

/*
 * The maximal hash length that can be encoded in a name
 * using base32hex.  floor(255/8)*5
 */
#define NSEC3_MAX_HASH_LENGTH 155

/*
 * The maximum has that can be encoded in a single label using
 * base32hex.  floor(63/8)*5
 */
#define NSEC3_MAX_LABEL_HASH 35

ISC_LANG_BEGINDECLS

int
isc_iterated_hash(unsigned char *out, const unsigned int hashalg,
		  const int iterations, const unsigned char *salt,
		  const int saltlength, const unsigned char *in,
		  const int inlength);

ISC_LANG_ENDDECLS
