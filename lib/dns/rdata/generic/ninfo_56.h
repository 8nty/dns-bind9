/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/* */
#ifndef GENERIC_NINFO_56_H
#define GENERIC_NINFO_56_H 1

typedef struct dns_rdata_txt_string dns_rdata_ninfo_string_t;

typedef struct dns_rdata_txt dns_rdata_ninfo_t;

/*
 * ISC_LANG_BEGINDECLS and ISC_LANG_ENDDECLS are already done
 * via rdatastructpre.h and rdatastructsuf.h.
 */

isc_result_t
dns_rdata_ninfo_first(dns_rdata_ninfo_t *);

isc_result_t
dns_rdata_ninfo_next(dns_rdata_ninfo_t *);

isc_result_t
dns_rdata_ninfo_current(dns_rdata_ninfo_t *, dns_rdata_ninfo_string_t *);

#endif /* GENERIC_NINFO_16_H */
