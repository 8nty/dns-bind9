/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_OPT_41_H
#define GENERIC_OPT_41_H 1

/*!
 *  \brief Per RFC2671 */

typedef struct dns_rdata_opt_opcode {
	uint16_t opcode;
	uint16_t length;
	unsigned char *data;
} dns_rdata_opt_opcode_t;

typedef struct dns_rdata_opt {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	unsigned char *options;
	uint16_t length;
	/* private */
	uint16_t offset;
} dns_rdata_opt_t;

/*
 * ISC_LANG_BEGINDECLS and ISC_LANG_ENDDECLS are already done
 * via rdatastructpre.h and rdatastructsuf.h.
 */

isc_result_t
dns_rdata_opt_first(dns_rdata_opt_t *);

isc_result_t
dns_rdata_opt_next(dns_rdata_opt_t *);

isc_result_t
dns_rdata_opt_current(dns_rdata_opt_t *, dns_rdata_opt_opcode_t *);

#endif /* GENERIC_OPT_41_H */
