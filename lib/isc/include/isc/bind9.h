/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_BIND9_H
#define ISC_BIND9_H 1

#include <stdbool.h>

#include <isc/platform.h>

/*
 * This determines whether we are using the libisc/libdns libraries
 * in BIND9 or in some other application.  For BIND9 (named and related
 * tools) it must be set to true at runtime.  Export library clients
 * will call isc_lib_register(), which will set it to false.
 */
LIBISC_EXTERNAL_DATA extern bool isc_bind9;

#endif /* ISC_BIND9_H */
