/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/*! \file isc/utf8.h */

#pragma once

#include <isc/lang.h>
#include <isc/types.h>

ISC_LANG_BEGINDECLS

bool
isc_utf8_bom(const unsigned char *buf, size_t len);
/*<
 * Returns 'true' if the string of bytes in 'buf' starts
 * with an UTF-8 Byte Order Mark.
 *
 * Requires:
 *\li 	'buf' != NULL
 */

bool
isc_utf8_valid(const unsigned char *buf, size_t len);
/*<
 * Returns 'true' if the string of bytes in 'buf' is a valid UTF-8
 * byte sequence otherwise 'false' is returned.
 *
 * Requires:
 *\li 	'buf' != NULL
 */

ISC_LANG_ENDDECLS
