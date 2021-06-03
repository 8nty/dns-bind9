/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/*! \file */

#ifndef RNDC_OS_H
#define RNDC_OS_H 1

#include <stdio.h>

#include <isc/lang.h>

ISC_LANG_BEGINDECLS

int
set_user(FILE *fd, const char *user);
/*%<
 * Set the owner of the file referenced by 'fd' to 'user'.
 * Returns:
 *   0 		success
 *   -1 	insufficient permissions, or 'user' does not exist.
 */

ISC_LANG_ENDDECLS

#endif /* ifndef RNDC_OS_H */
