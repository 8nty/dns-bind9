/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

/*! \file */

#include <isc/lang.h>
#include <isc/types.h>

#include <dns/transport.h>

#include <isccfg/cfg.h>

ISC_LANG_BEGINDECLS

isc_result_t
named_transports_fromconfig(const cfg_obj_t *config, const cfg_obj_t *vconfig,
			    isc_mem_t *mctx, dns_transport_list_t **listp);
/*%<
 * Create a list of transport objects (DoT or DoH) and configure them
 * according to 'key-file', 'cert-file', 'ca-file' or 'hostname'
 * statements.
 *
 *	Requires:
 *	\li	'config' is not NULL.
 *	\li	'vconfig' is not NULL.
 *	\li	'mctx' is not NULL
 *	\li	'listp' is not NULL, and '*listp' is NULL
 *
 */

ISC_LANG_ENDDECLS
