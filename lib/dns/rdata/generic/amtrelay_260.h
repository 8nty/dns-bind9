/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_AMTRELAY_260_H
#define GENERIC_AMTRELAY_260_H 1

typedef struct dns_rdata_amtrelay {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint8_t precedence;
	bool discovery;
	uint8_t gateway_type;
	struct in_addr in_addr;	  /* gateway type 1 */
	struct in6_addr in6_addr; /* gateway type 2 */
	dns_name_t gateway;	  /* gateway type 3 */
	unsigned char *data;	  /* gateway type > 3 */
	uint16_t length;
} dns_rdata_amtrelay_t;

#endif /* GENERIC_AMTRELAY_260_H */
