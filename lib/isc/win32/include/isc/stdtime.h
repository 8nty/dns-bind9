/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_STDTIME_H
#define ISC_STDTIME_H 1

#include <inttypes.h>
#include <stdlib.h>

#include <isc/lang.h>

/*
 * It's public information that 'isc_stdtime_t' is an unsigned integral type.
 * Applications that want maximum portability should not assume anything
 * about its size.
 */
typedef uint32_t isc_stdtime_t;

ISC_LANG_BEGINDECLS

void
isc_stdtime_get(isc_stdtime_t *t);
/*
 * Set 't' to the number of seconds since 00:00:00 UTC, January 1, 1970.
 *
 * Requires:
 *
 *	't' is a valid pointer.
 */

void
isc_stdtime_tostring(isc_stdtime_t t, char *out, size_t outlen);
/*
 * Convert 't' into a null-terminated string of the form
 * "Wed Jun 30 21:49:08 1993". Store the string in the 'out'
 * buffer.
 *
 * Requires:
 *
 *	't' is a valid time.
 *	'out' is a valid pointer.
 *	'outlen' is at least 26.
 */

#define isc_stdtime_convert32(t, t32p) (*(t32p) = t)
/*
 * Convert the standard time to its 32-bit version.
 */

ISC_LANG_ENDDECLS

#endif /* ISC_STDTIME_H */
