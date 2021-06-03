/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_SYSLOG_H
#define ISC_SYSLOG_H 1

#include <isc/lang.h>
#include <isc/types.h>

ISC_LANG_BEGINDECLS

isc_result_t
isc_syslog_facilityfromstring(const char *str, int *facilityp);
/*
 * Convert 'str' to the appropriate syslog facility constant.
 *
 * Requires:
 *
 *	'str' is not NULL
 *	'facilityp' is not NULL
 *
 * Returns:
 * 	ISC_R_SUCCESS
 * 	ISC_R_NOTFOUND
 */

ISC_LANG_ENDDECLS

#endif /* ISC_SYSLOG_H */
