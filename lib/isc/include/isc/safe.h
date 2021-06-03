/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_SAFE_H
#define ISC_SAFE_H 1

/*! \file isc/safe.h */

#include <isc/lang.h>

ISC_LANG_BEGINDECLS

int
isc_safe_memequal(const void *, const void *, size_t);

/*%<
 * Returns true iff. two blocks of memory are equal, otherwise
 * false.
 *
 */

void
isc_safe_memwipe(void *, size_t);

/*%<
 * Clear the memory of length `len` pointed to by `ptr`.
 *
 * Some crypto code calls memset() on stack allocated buffers just
 * before return so that they are wiped. Such memset() calls can be
 * optimized away by the compiler. We provide this external non-inline C
 * function to perform the memset operation so that the compiler cannot
 * infer about what the function does and optimize the call away.
 */

ISC_LANG_ENDDECLS

#endif /* ISC_SAFE_H */
