/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_WIN32OS_H
#define ISC_WIN32OS_H 1

#include <isc/lang.h>

ISC_LANG_BEGINDECLS

/*
 * Return the number of CPUs available on the system, or 1 if this cannot
 * be determined.
 */

int
isc_win32os_versioncheck(unsigned int major, unsigned int minor,
			 unsigned int updatemajor, unsigned int updateminor);

/*
 * Checks the current version of the operating system with the
 * supplied version information.
 * Returns:
 * -1	if less than the version information supplied
 *  0   if equal to all of the version information supplied
 * +1   if greater than the version information supplied
 */

ISC_LANG_ENDDECLS

#endif /* ISC_WIN32OS_H */
