/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/*! \file */

#include <stdlib.h>
#include <string.h>

#include <isc/region.h>
#include <isc/util.h>

int
isc_region_compare(isc_region_t *r1, isc_region_t *r2) {
	unsigned int l;
	int result;

	REQUIRE(r1 != NULL);
	REQUIRE(r2 != NULL);

	l = (r1->length < r2->length) ? r1->length : r2->length;

	if ((result = memcmp(r1->base, r2->base, l)) != 0) {
		return ((result < 0) ? -1 : 1);
	} else {
		return ((r1->length == r2->length)  ? 0
			: (r1->length < r2->length) ? -1
						    : 1);
	}
}
