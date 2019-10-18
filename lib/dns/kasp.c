/*
 * Copyright (C) Internet Systems Consortium, Inc. ("ISC")
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * See the COPYRIGHT file distributed with this work for additional
 * information regarding copyright ownership.
 */

/*! \file */

#include <string.h>

#include <isc/assertions.h>
#include <isc/file.h>
#include <isc/log.h>
#include <isc/mem.h>
#include <isc/util.h>

#include <dns/log.h>
#include <dns/kasp.h>

isc_result_t
dns_kasp_create(isc_mem_t *mctx, const char *name, dns_kasp_t **kaspp)
{
	dns_kasp_t *kasp;

	REQUIRE(name != NULL);
	REQUIRE(kaspp != NULL && *kaspp == NULL);

	kasp = isc_mem_get(mctx, sizeof(*kasp));
	kasp->mctx = NULL;
	isc_mem_attach(mctx, &kasp->mctx);

	kasp->name = isc_mem_strdup(mctx, name);
	isc_mutex_init(&kasp->lock);
	kasp->frozen = false;

	isc_refcount_init(&kasp->references, 1);

	ISC_LINK_INIT(kasp, link);
	kasp->kasplist = NULL;

	kasp->signatures_resign = DNS_KASP_SIG_RESIGN;
	kasp->signatures_refresh = DNS_KASP_SIG_REFRESH;
	kasp->signatures_validity = DNS_KASP_SIG_VALIDITY;
	kasp->signatures_validity_dnskey = DNS_KASP_SIG_VALIDITY_DNSKEY;
	kasp->signatures_validity_denial = DNS_KASP_SIG_VALIDITY_DENIAL;
	kasp->signatures_jitter = DNS_KASP_SIG_JITTER;
	kasp->signatures_inception_offset = DNS_KASP_SIG_INCEPTION_OFFSET;

	// TODO: The rest of the KASP configuration

	kasp->magic = DNS_KASP_MAGIC;
	*kaspp = kasp;

	return (ISC_R_SUCCESS);
}

void
dns_kasp_attach(dns_kasp_t *source, dns_kasp_t **targetp) {
	REQUIRE(DNS_KASP_VALID(source));
	REQUIRE(targetp != NULL && *targetp == NULL);
	isc_refcount_increment(&source->references);
	*targetp = source;
}

static inline void
destroy(dns_kasp_t *kasp) {
	isc_mem_free(kasp->mctx, kasp->dbfile);
	isc_mem_free(kasp->mctx, kasp->name);
	isc_mem_putanddetach(&kasp->mctx, kasp, sizeof(*kasp));
}

void
dns_kasp_detach(dns_kasp_t **kaspp) {
	REQUIRE(kaspp != NULL && DNS_KASP_VALID(*kaspp));
	dns_kasp_t *kasp = *kaspp;
	*kaspp = NULL;

	if (isc_refcount_decrement(&kasp->references) == 1) {
		destroy(kasp);
	}
}

void
dns_kasp_freeze(dns_kasp_t *kasp) {
	REQUIRE(DNS_KASP_VALID(kasp));
	REQUIRE(!kasp->frozen);
	kasp->frozen = true;
}

void
dns_kasp_thaw(dns_kasp_t *kasp) {
	REQUIRE(DNS_KASP_VALID(kasp));
	REQUIRE(kasp->frozen);
	kasp->frozen = false;
}

isc_result_t
dns_kasplist_find(dns_kasplist_t *list, const char *name, dns_kasp_t **kaspp)
{
	dns_kasp_t *kasp;

	if (list == NULL) {
		return (ISC_R_NOTFOUND);
	}
	INSIST(list != NULL);

	dns_kasp_t *kasp;
	for (kasp = ISC_LIST_HEAD(*list);
	     kasp != NULL;
	     kasp = ISC_LIST_NEXT(kasp, link))
	{
		if (strcmp(kasp->name, name) == 0) {
			break;
		}
	}
	if (kasp == NULL) {
		return (ISC_R_NOTFOUND);
	}
	dns_kasp_attach(kasp, kaspp);
	return (ISC_R_SUCCESS);
}
