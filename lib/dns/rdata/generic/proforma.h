/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_PROFORMA_H
#define GENERIC_PROFORMA_H 1

typedef struct dns_rdata_ #{
	dns_rdatacommon_t common;
	isc_mem_t *mctx; /* if required */
			 /* type & class specific elements */
}
dns_rdata_ #_t;

#endif /* GENERIC_PROFORMA_H */
