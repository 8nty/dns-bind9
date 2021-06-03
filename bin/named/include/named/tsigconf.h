/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef NAMED_TSIGCONF_H
#define NAMED_TSIGCONF_H 1

/*! \file */

#include <isc/lang.h>
#include <isc/types.h>

ISC_LANG_BEGINDECLS

isc_result_t
named_tsigkeyring_fromconfig(const cfg_obj_t *config, const cfg_obj_t *vconfig,
			     isc_mem_t *mctx, dns_tsig_keyring_t **ringp);
/*%<
 * Create a TSIG key ring and configure it according to the 'key'
 * statements in the global and view configuration objects.
 *
 *	Requires:
 *	\li	'config' is not NULL.
 *	\li	'vconfig' is not NULL.
 *	\li	'mctx' is not NULL
 *	\li	'ringp' is not NULL, and '*ringp' is NULL
 *
 *	Returns:
 *	\li	ISC_R_SUCCESS
 *	\li	ISC_R_NOMEMORY
 */

ISC_LANG_ENDDECLS

#endif /* NAMED_TSIGCONF_H */
