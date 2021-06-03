/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_MEMINFO_H
#define ISC_MEMINFO_H 1

#include <inttypes.h>

#include <isc/lang.h>
#include <isc/types.h>

ISC_LANG_BEGINDECLS

uint64_t
isc_meminfo_totalphys(void);
/*%<
 * Return total available physical memory in bytes, or 0 if this cannot
 * be determined
 */

ISC_LANG_ENDDECLS

#endif /* ISC_MEMINFO_H */
