/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef DNS_BIT_H
#define DNS_BIT_H 1

/*! \file dns/bit.h */

#include <inttypes.h>

typedef uint64_t dns_bitset_t;

#define DNS_BIT_SET(bit, bitset)   (*(bitset) |= ((dns_bitset_t)1 << (bit)))
#define DNS_BIT_CLEAR(bit, bitset) (*(bitset) &= ~((dns_bitset_t)1 << (bit)))
#define DNS_BIT_CHECK(bit, bitset) \
	((*(bitset) & ((dns_bitset_t)1 << (bit))) == ((dns_bitset_t)1 << (bit)))

#endif /* DNS_BIT_H */
