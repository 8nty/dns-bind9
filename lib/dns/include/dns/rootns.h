/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef DNS_ROOTNS_H
#define DNS_ROOTNS_H 1

/*! \file dns/rootns.h */

#include <isc/lang.h>

#include <dns/types.h>

ISC_LANG_BEGINDECLS

isc_result_t
dns_rootns_create(isc_mem_t *mctx, dns_rdataclass_t rdclass,
		  const char *filename, dns_db_t **target);

void
dns_root_checkhints(dns_view_t *view, dns_db_t *hints, dns_db_t *db);
/*
 * Reports differences between hints and the real roots.
 *
 * Requires view, hints and (cache) db to be valid.
 */

ISC_LANG_ENDDECLS

#endif /* DNS_ROOTNS_H */
