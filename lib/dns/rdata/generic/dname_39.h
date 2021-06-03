/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_DNAME_39_H
#define GENERIC_DNAME_39_H 1

/*!
 *  \brief per RFC2672 */

typedef struct dns_rdata_dname {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t dname;
} dns_rdata_dname_t;

#endif /* GENERIC_DNAME_39_H */
