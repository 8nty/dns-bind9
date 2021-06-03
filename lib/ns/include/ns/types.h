/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef NS_TYPES_H
#define NS_TYPES_H 1

/*! \file */

typedef struct ns_altsecret ns_altsecret_t;
typedef ISC_LIST(ns_altsecret_t) ns_altsecretlist_t;
typedef struct ns_client    ns_client_t;
typedef struct ns_clientmgr ns_clientmgr_t;
typedef struct ns_plugin    ns_plugin_t;
typedef ISC_LIST(ns_plugin_t) ns_plugins_t;
typedef struct ns_interface    ns_interface_t;
typedef struct ns_interfacemgr ns_interfacemgr_t;
typedef struct ns_query	       ns_query_t;
typedef struct ns_server       ns_server_t;
typedef struct ns_stats	       ns_stats_t;
typedef struct ns_hookasync    ns_hookasync_t;

typedef enum { ns_cookiealg_aes, ns_cookiealg_siphash24 } ns_cookiealg_t;

#define NS_COOKIE_VERSION_1 1

#endif /* NS_TYPES_H */
