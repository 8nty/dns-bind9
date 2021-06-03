/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_NETSCOPE_H
#define ISC_NETSCOPE_H 1

/*! \file isc/netscope.h */

#include <inttypes.h>

ISC_LANG_BEGINDECLS

/*%
 * Convert a string of an IPv6 scope zone to zone index.  If the conversion
 * succeeds, 'zoneid' will store the index value.
 *
 * XXXJT: when a standard interface for this purpose is defined,
 * we should use it.
 *
 * Returns:
 * \li	ISC_R_SUCCESS: conversion succeeds
 * \li	ISC_R_FAILURE: conversion fails
 */
isc_result_t
isc_netscope_pton(int af, char *scopename, void *addr, uint32_t *zoneid);

ISC_LANG_ENDDECLS

#endif /* ISC_NETSCOPE_H */
