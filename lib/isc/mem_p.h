/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

#include <stdio.h>

#include <isc/mem.h>

/*! \file */

void
isc__mem_printactive(isc_mem_t *mctx, FILE *file);
/*%<
 * For use by unit tests, prints active memory blocks for
 * a single memory context.
 */

void
isc__mem_checkdestroyed(void);

void
isc__mem_initialize(void);

void
isc__mem_shutdown(void);
