/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_OFFSET_H
#define ISC_OFFSET_H 1

/*! \file
 * \brief
 * File offsets are operating-system dependent.
 */
#include <limits.h> /* Required for CHAR_BIT. */
#include <stddef.h> /* For Linux Standard Base. */

#include <sys/types.h>

typedef off_t isc_offset_t;

#endif /* ISC_OFFSET_H */
