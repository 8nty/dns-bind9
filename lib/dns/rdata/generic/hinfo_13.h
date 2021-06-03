/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef GENERIC_HINFO_13_H
#define GENERIC_HINFO_13_H 1

typedef struct dns_rdata_hinfo {
	dns_rdatacommon_t common;
	isc_mem_t *mctx;
	char *cpu;
	char *os;
	uint8_t cpu_len;
	uint8_t os_len;
} dns_rdata_hinfo_t;

#endif /* GENERIC_HINFO_13_H */
