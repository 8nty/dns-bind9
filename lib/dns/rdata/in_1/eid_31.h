/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef IN_1_EID_31_H
#define IN_1_EID_31_H 1

/*!
 *  \brief http://ana-3.lcs.mit.edu/~jnc/nimrod/dns.txt
 */

typedef struct dns_rdata_in_eid {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	unsigned char *eid;
	uint16_t eid_len;
} dns_rdata_in_eid_t;

#endif /* IN_1_EID_31_H */
