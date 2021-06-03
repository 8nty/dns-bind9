/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

/*! \file isc/string.h */

#include <string.h>

#include "isc/lang.h"
#include "isc/platform.h"

ISC_LANG_BEGINDECLS

#if !defined(HAVE_STRLCPY)
size_t
strlcpy(char *dst, const char *src, size_t size);
#endif /* !defined(HAVE_STRLCPY) */

#if !defined(HAVE_STRLCAT)
size_t
strlcat(char *dst, const char *src, size_t size);
#endif /* if !defined(HAVE_STRLCAT) */

int
isc_string_strerror_r(int errnum, char *buf, size_t buflen);

ISC_LANG_ENDDECLS
