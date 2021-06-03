/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_LIKELY_H
#define ISC_LIKELY_H 1

/*%
 * Performance
 */
#ifdef CPPCHECK
#define ISC_LIKELY(x)	(x)
#define ISC_UNLIKELY(x) (x)
#else /* ifdef CPPCHECK */
#ifdef HAVE_BUILTIN_EXPECT
#define ISC_LIKELY(x)	__builtin_expect(!!(x), 1)
#define ISC_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else /* ifdef HAVE_BUILTIN_EXPECT */
#define ISC_LIKELY(x)	(x)
#define ISC_UNLIKELY(x) (x)
#endif /* ifdef HAVE_BUILTIN_EXPECT */
#endif /* ifdef CPPCHECK */

#endif /* ISC_LIKELY_H */
