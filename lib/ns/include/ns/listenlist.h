/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef NS_LISTENLIST_H
#define NS_LISTENLIST_H 1

/*****
***** Module Info
*****/

/*! \file
 * \brief
 * "Listen lists", as in the "listen-on" configuration statement.
 */

/***
 *** Imports
 ***/

#include <stdbool.h>

#include <isc/net.h>
#include <isc/tls.h>

#include <dns/types.h>

/***
 *** Types
 ***/

typedef struct ns_listenelt  ns_listenelt_t;
typedef struct ns_listenlist ns_listenlist_t;

struct ns_listenelt {
	isc_mem_t *   mctx;
	in_port_t     port;
	bool	      is_http;
	isc_dscp_t    dscp; /* -1 = not set, 0..63 */
	dns_acl_t *   acl;
	isc_tlsctx_t *sslctx;
	char **	      http_endpoints;
	size_t	      http_endpoints_number;
	ISC_LINK(ns_listenelt_t) link;
};

struct ns_listenlist {
	isc_mem_t *mctx;
	int	   refcount;
	ISC_LIST(ns_listenelt_t) elts;
};

/***
 *** Functions
 ***/

isc_result_t
ns_listenelt_create(isc_mem_t *mctx, in_port_t port, isc_dscp_t dscp,
		    dns_acl_t *acl, bool tls, const char *key, const char *cert,
		    ns_listenelt_t **target);
/*%<
 * Create a listen-on list element.
 */

isc_result_t
ns_listenelt_create_http(isc_mem_t *mctx, in_port_t http_port, isc_dscp_t dscp,
			 dns_acl_t *acl, bool tls, const char *key,
			 const char *cert, char **endpoints, size_t nendpoints,
			 ns_listenelt_t **target);
/*%<
 * Create a listen-on list element for HTTP(S).
 */

void
ns_listenelt_destroy(ns_listenelt_t *elt);
/*%<
 * Destroy a listen-on list element.
 */

isc_result_t
ns_listenlist_create(isc_mem_t *mctx, ns_listenlist_t **target);
/*%<
 * Create a new, empty listen-on list.
 */

void
ns_listenlist_attach(ns_listenlist_t *source, ns_listenlist_t **target);
/*%<
 * Attach '*target' to '*source'.
 */

void
ns_listenlist_detach(ns_listenlist_t **listp);
/*%<
 * Detach 'listp'.
 */

isc_result_t
ns_listenlist_default(isc_mem_t *mctx, in_port_t port, isc_dscp_t dscp,
		      bool enabled, ns_listenlist_t **target);
/*%<
 * Create a listen-on list with default contents, matching
 * all addresses with port 'port' (if 'enabled' is true),
 * or no addresses (if 'enabled' is false).
 */

#endif /* NS_LISTENLIST_H */
