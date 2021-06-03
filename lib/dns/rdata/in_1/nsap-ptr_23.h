/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef IN_1_NSAP_PTR_23_H
#define IN_1_NSAP_PTR_23_H 1

/*!
 *  \brief Per RFC1348.  Obsoleted in RFC 1706 - use PTR instead. */

typedef struct dns_rdata_in_nsap_ptr {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t owner;
} dns_rdata_in_nsap_ptr_t;

#endif /* IN_1_NSAP_PTR_23_H */
