/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef DNS_RDATASTRUCT_H
#define DNS_RDATASTRUCT_H 1

#include <isc/lang.h>
#include <isc/sockaddr.h>

#include <dns/name.h>
#include <dns/types.h>

ISC_LANG_BEGINDECLS

typedef struct dns_rdatacommon {
	dns_rdataclass_t rdclass;
	dns_rdatatype_t rdtype;
	ISC_LINK(struct dns_rdatacommon) link;
} dns_rdatacommon_t;

#define DNS_RDATACOMMON_INIT(_data, _rdtype, _rdclass) \
	do {                                           \
		(_data)->common.rdtype = (_rdtype);    \
		(_data)->common.rdclass = (_rdclass);  \
		ISC_LINK_INIT(&(_data)->common, link); \
	} while (0)
