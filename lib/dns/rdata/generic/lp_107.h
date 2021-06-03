/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_LP_107_H
#define GENERIC_LP_107_H 1

typedef struct dns_rdata_lp {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	uint16_t pref;
	dns_name_t lp;
} dns_rdata_lp_t;

#endif /* GENERIC_LP_107_H */
