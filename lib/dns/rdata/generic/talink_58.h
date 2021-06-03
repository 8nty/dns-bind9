/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/*
 * http://www.iana.org/assignments/dns-parameters/TALINK/talink-completed-template
 */

#ifndef GENERIC_TALINK_58_H
#define GENERIC_TALINK_58_H 1

typedef struct dns_rdata_talink {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	dns_name_t prev;
	dns_name_t next;
} dns_rdata_talink_t;

#endif /* GENERIC_TALINK_58_H */
