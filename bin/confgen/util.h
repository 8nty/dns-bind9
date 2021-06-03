/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef RNDC_UTIL_H
#define RNDC_UTIL_H 1

/*! \file */

#include <isc/attributes.h>
#include <isc/formatcheck.h>
#include <isc/lang.h>
#include <isc/platform.h>

#define NS_CONTROL_PORT 953

#undef DO
#define DO(name, function)                                                \
	do {                                                              \
		result = function;                                        \
		if (result != ISC_R_SUCCESS)                              \
			fatal("%s: %s", name, isc_result_totext(result)); \
		else                                                      \
			notify("%s", name);                               \
	} while (0)

ISC_LANG_BEGINDECLS

void
notify(const char *fmt, ...) ISC_FORMAT_PRINTF(1, 2);

ISC_NORETURN void
fatal(const char *format, ...) ISC_FORMAT_PRINTF(1, 2);

ISC_LANG_ENDDECLS

#endif /* RNDC_UTIL_H */
