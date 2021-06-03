/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

/*! \file include/ns/lib.h */

#include <isc/lang.h>
#include <isc/types.h>

ISC_LANG_BEGINDECLS

LIBNS_EXTERNAL_DATA extern unsigned int ns_pps;

isc_result_t
ns_lib_init(void);
/*%<
 * A set of initialization procedures used in the NS library.
 */

void
ns_lib_shutdown(void);
/*%<
 * Free temporary resources allocated in ns_lib_init().
 */

ISC_LANG_ENDDECLS
