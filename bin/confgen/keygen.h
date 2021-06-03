/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef RNDC_KEYGEN_H
#define RNDC_KEYGEN_H 1

/*! \file */

#include <isc/buffer.h>
#include <isc/lang.h>
#include <isc/mem.h>

#include <dns/secalg.h>

ISC_LANG_BEGINDECLS

void
generate_key(isc_mem_t *mctx, dns_secalg_t alg, int keysize,
	     isc_buffer_t *key_txtbuffer);

void
write_key_file(const char *keyfile, const char *user, const char *keyname,
	       isc_buffer_t *secret, dns_secalg_t alg);

const char *
alg_totext(dns_secalg_t alg);
dns_secalg_t
alg_fromtext(const char *name);
int
alg_bits(dns_secalg_t alg);

ISC_LANG_ENDDECLS

#endif /* RNDC_KEYGEN_H */
