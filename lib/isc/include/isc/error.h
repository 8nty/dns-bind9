/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_ERROR_H
#define ISC_ERROR_H 1

/*! \file isc/error.h */

#include <stdarg.h>

#include <isc/attributes.h>
#include <isc/formatcheck.h>
#include <isc/lang.h>
#include <isc/likely.h>
#include <isc/platform.h>

ISC_LANG_BEGINDECLS

typedef void (*isc_errorcallback_t)(const char *, int, const char *, va_list);

/*% set unexpected error */
void isc_error_setunexpected(isc_errorcallback_t);

/*% set fatal error */
void isc_error_setfatal(isc_errorcallback_t);

/*% unexpected error */
void
isc_error_unexpected(const char *, int, const char *, ...)
	ISC_FORMAT_PRINTF(3, 4);

/*% fatal error */
ISC_NORETURN void
isc_error_fatal(const char *, int, const char *, ...) ISC_FORMAT_PRINTF(3, 4);

/*% runtimecheck error */
ISC_NORETURN void
isc_error_runtimecheck(const char *, int, const char *);

#define ISC_ERROR_RUNTIMECHECK(cond) \
	((void)(ISC_LIKELY(cond) ||  \
		((isc_error_runtimecheck)(__FILE__, __LINE__, #cond), 0)))

ISC_LANG_ENDDECLS

#endif /* ISC_ERROR_H */
