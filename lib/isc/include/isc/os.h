/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_OS_H
#define ISC_OS_H 1

/*! \file isc/os.h */

#include <isc/lang.h>

ISC_LANG_BEGINDECLS

unsigned int
isc_os_ncpus(void);
/*%<
 * Return the number of CPUs available on the system, or 1 if this cannot
 * be determined.
 */

ISC_LANG_ENDDECLS

#endif /* ISC_OS_H */
