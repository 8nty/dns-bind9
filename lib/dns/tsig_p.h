/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef DNS_TSIG_P_H
#define DNS_TSIG_P_H

/*! \file */

#include <stdbool.h>

#include <isc/result.h>

#include <dns/types.h>

/*%
 *     These functions must not be used outside this module and
 *     its associated unit tests.
 */

ISC_LANG_BEGINDECLS

bool
dns__tsig_algvalid(unsigned int alg);
unsigned int
dns__tsig_algfromname(const dns_name_t *algorithm);
const dns_name_t *
dns__tsig_algnamefromname(const dns_name_t *algorithm);
bool
dns__tsig_algallocated(const dns_name_t *algorithm);

ISC_LANG_ENDDECLS

#endif /* DNS_TSIG_P_H */
