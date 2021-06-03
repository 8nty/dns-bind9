/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef DNS_ZONEKEY_H
#define DNS_ZONEKEY_H 1

/*! \file dns/zonekey.h */

#include <stdbool.h>

#include <isc/lang.h>

#include <dns/types.h>

ISC_LANG_BEGINDECLS

bool
dns_zonekey_iszonekey(dns_rdata_t *keyrdata);
/*%<
 *	Determines if the key record contained in the rdata is a zone key.
 *
 *	Requires:
 *		'keyrdata' is not NULL.
 */

ISC_LANG_ENDDECLS

#endif /* DNS_ZONEKEY_H */
