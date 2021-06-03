/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#include <isc/fuzz.h>

#ifndef NAMED_FUZZ_H
#define NAMED_FUZZ_H

void
named_fuzz_notify(void);

void
named_fuzz_setup(void);

#endif /* NAMED_FUZZ_H */
