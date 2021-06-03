/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef DNS_KEYDATA_H
#define DNS_KEYDATA_H 1

/*****
***** Module Info
*****/

/*! \file dns/keydata.h
 * \brief
 * KEYDATA utilities.
 */

/***
 *** Imports
 ***/

#include <inttypes.h>

#include <isc/lang.h>
#include <isc/types.h>

#include <dns/rdatastruct.h>
#include <dns/types.h>

ISC_LANG_BEGINDECLS

isc_result_t
dns_keydata_todnskey(dns_rdata_keydata_t *keydata, dns_rdata_dnskey_t *dnskey,
		     isc_mem_t *mctx);

isc_result_t
dns_keydata_fromdnskey(dns_rdata_keydata_t *keydata, dns_rdata_dnskey_t *dnskey,
		       uint32_t refresh, uint32_t addhd, uint32_t removehd,
		       isc_mem_t *mctx);

ISC_LANG_ENDDECLS

#endif /* DNS_KEYDATA_H */
