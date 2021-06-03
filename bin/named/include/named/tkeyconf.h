/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef NAMED_TKEYCONF_H
#define NAMED_TKEYCONF_H 1

/*! \file */

#include <isc/lang.h>
#include <isc/types.h>

#include <isccfg/cfg.h>

ISC_LANG_BEGINDECLS

isc_result_t
named_tkeyctx_fromconfig(const cfg_obj_t *options, isc_mem_t *mctx,
			 dns_tkeyctx_t **tctxp);
/*%<
 * 	Create a TKEY context and configure it, including the default DH key
 *	and default domain, according to 'options'.
 *
 *	Requires:
 *\li		'cfg' is a valid configuration options object.
 *\li		'mctx' is not NULL
 *\li		'tctx' is not NULL
 *\li		'*tctx' is NULL
 *
 *	Returns:
 *\li		ISC_R_SUCCESS
 *\li		ISC_R_NOMEMORY
 */

ISC_LANG_ENDDECLS

#endif /* NAMED_TKEYCONF_H */
