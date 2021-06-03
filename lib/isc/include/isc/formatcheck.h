/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_FORMATCHECK_H
#define ISC_FORMATCHECK_H 1

/*! \file isc/formatcheck.h */

/*%
 * ISC_FORMAT_PRINTF().
 *
 * \li fmt is the location of the format string parameter.
 * \li args is the location of the first argument (or 0 for no argument
 * checking).
 *
 * Note:
 * \li The first parameter is 1, not 0.
 */
#ifdef __GNUC__
#define ISC_FORMAT_PRINTF(fmt, args) \
	__attribute__((__format__(__printf__, fmt, args)))
#else /* ifdef __GNUC__ */
#define ISC_FORMAT_PRINTF(fmt, args)
#endif /* ifdef __GNUC__ */

#endif /* ISC_FORMATCHECK_H */
