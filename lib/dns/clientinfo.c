/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/*! \file */

#include <dns/clientinfo.h>

void
dns_clientinfomethods_init(dns_clientinfomethods_t *methods,
			   dns_clientinfo_sourceip_t sourceip) {
	methods->version = DNS_CLIENTINFOMETHODS_VERSION;
	methods->age = DNS_CLIENTINFOMETHODS_AGE;
	methods->sourceip = sourceip;
}

void
dns_clientinfo_init(dns_clientinfo_t *ci, void *data, void *versionp) {
	ci->version = DNS_CLIENTINFO_VERSION;
	ci->data = data;
	ci->dbversion = versionp;
}
