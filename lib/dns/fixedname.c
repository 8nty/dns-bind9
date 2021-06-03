/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/*! \file */

#include <dns/fixedname.h>

void
dns_fixedname_init(dns_fixedname_t *fixed) {
	dns_name_init(&fixed->name, fixed->offsets);
	isc_buffer_init(&fixed->buffer, fixed->data, DNS_NAME_MAXWIRE);
	dns_name_setbuffer(&fixed->name, &fixed->buffer);
}

void
dns_fixedname_invalidate(dns_fixedname_t *fixed) {
	dns_name_invalidate(&fixed->name);
}

dns_name_t *
dns_fixedname_name(dns_fixedname_t *fixed) {
	return (&fixed->name);
}

dns_name_t *
dns_fixedname_initname(dns_fixedname_t *fixed) {
	dns_fixedname_init(fixed);
	return (dns_fixedname_name(fixed));
}
