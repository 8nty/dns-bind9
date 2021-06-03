/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef NAMED_LOGCONF_H
#define NAMED_LOGCONF_H 1

/*! \file */

#include <isc/log.h>

isc_result_t
named_logconfig(isc_logconfig_t *logconf, const cfg_obj_t *logstmt);
/*%<
 * Set up the logging configuration in '*logconf' according to
 * the named.conf data in 'logstmt'.
 */

#endif /* NAMED_LOGCONF_H */
