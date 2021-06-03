/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_OFFSET_H
#define ISC_OFFSET_H 1

/*
 * File offsets are operating-system dependent.
 */
#include <limits.h> /* Required for CHAR_BIT. */

#include <sys/types.h>

typedef _off_t isc_offset_t;

#endif /* ISC_OFFSET_H */
