/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef UNIX_ERRNO2RESULT_H
#define UNIX_ERRNO2RESULT_H 1

/*! \file */

/* XXXDCL this should be moved to lib/isc/include/isc/errno2result.h. */

#include <errno.h> /* Provides errno. */
#include <stdbool.h>

#include <isc/lang.h>
#include <isc/types.h>

ISC_LANG_BEGINDECLS

#define isc__errno2result(x) isc___errno2result(x, true, __FILE__, __LINE__)

isc_result_t
isc___errno2result(int posixerrno, bool dolog, const char *file,
		   unsigned int line);

ISC_LANG_ENDDECLS

#endif /* UNIX_ERRNO2RESULT_H */
