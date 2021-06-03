/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_NTGROUPS_H
#define ISC_NTGROUPS_H 1

#include <isc/lang.h>
#include <isc/result.h>

ISC_LANG_BEGINDECLS

isc_result_t
isc_ntsecurity_getaccountgroups(char *name, char **Groups,
				unsigned int maxgroups, unsigned int *total);

ISC_LANG_ENDDECLS

#endif /* ISC_NTGROUPS_H */
