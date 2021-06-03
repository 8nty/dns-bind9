/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef CHECK_TOOL_H
#define CHECK_TOOL_H

/*! \file */

#include <inttypes.h>
#include <stdbool.h>

#include <isc/lang.h>
#include <isc/stdio.h>
#include <isc/types.h>

#include <dns/masterdump.h>
#include <dns/types.h>
#include <dns/zone.h>

ISC_LANG_BEGINDECLS

isc_result_t
setup_logging(isc_mem_t *mctx, FILE *errout, isc_log_t **logp);

isc_result_t
load_zone(isc_mem_t *mctx, const char *zonename, const char *filename,
	  dns_masterformat_t fileformat, const char *classname,
	  dns_ttl_t maxttl, dns_zone_t **zonep);

isc_result_t
dump_zone(const char *zonename, dns_zone_t *zone, const char *filename,
	  dns_masterformat_t fileformat, const dns_master_style_t *style,
	  const uint32_t rawversion);

#ifdef _WIN32
void
InitSockets(void);
void
DestroySockets(void);
#endif /* ifdef _WIN32 */

extern int debug;
extern const char *journal;
extern bool nomerge;
extern bool docheckmx;
extern bool docheckns;
extern bool dochecksrv;
extern dns_zoneopt_t zone_options;

ISC_LANG_ENDDECLS

#endif /* ifndef CHECK_TOOL_H */
