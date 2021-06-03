/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef NAMED_BUILTIN_H
#define NAMED_BUILTIN_H 1

/*! \file */

#include <isc/types.h>

isc_result_t
named_builtin_init(void);

void
named_builtin_deinit(void);

#endif /* NAMED_BUILTIN_H */
