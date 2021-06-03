/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/*! \file */

#include <stdbool.h>

#include <isc/bind9.h>

/*
 * This determines whether we are using the libisc/libdns libraries
 * in BIND9 or in some other application. It is initialized to true
 * and remains unchanged for BIND9 and related tools; export library
 * clients will run isc_lib_register(), which sets it to false,
 * overriding certain BIND9 behaviors.
 */
LIBISC_EXTERNAL_DATA bool isc_bind9 = true;
