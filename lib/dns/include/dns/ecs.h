/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef DNS_ECS_H
#define DNS_ECS_H 1

#include <inttypes.h>

#include <isc/lang.h>
#include <isc/netaddr.h>
#include <isc/types.h>

#include <dns/types.h>

struct dns_ecs {
	isc_netaddr_t addr;
	uint8_t	      source;
	uint8_t	      scope;
};

#define DNS_ECS_FORMATSIZE                                \
	(ISC_NETADDR_FORMATSIZE + 8) /* <address>/NNN/NNN \
				      */

ISC_LANG_BEGINDECLS

void
dns_ecs_init(dns_ecs_t *ecs);
/*%<
 * Initialize a DNS ECS structure.
 *
 * Requires:
 * \li 'ecs' is not NULL and points to a valid dns_ecs structure.
 */

void
dns_ecs_format(dns_ecs_t *ecs, char *buf, size_t size);
/*%<
 * Format an ECS record as text. Result is guaranteed to be null-terminated.
 *
 * Requires:
 * \li  'ecs' is not NULL.
 * \li  'buf' is not NULL.
 * \li  'size' is at least DNS_ECS_FORMATSIZE
 */

ISC_LANG_ENDDECLS

#endif /* DNS_ECS_H */
