/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_SOA_6_H
#define GENERIC_SOA_6_H 1

typedef struct dns_rdata_soa {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t origin;
	dns_name_t contact;
	uint32_t serial;  /*%< host order */
	uint32_t refresh; /*%< host order */
	uint32_t retry;	  /*%< host order */
	uint32_t expire;  /*%< host order */
	uint32_t minimum; /*%< host order */
} dns_rdata_soa_t;

#endif /* GENERIC_SOA_6_H */
