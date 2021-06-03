/*
 * SPDX-FileCopyrightText: Nominum, Inc.
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0 AND ISC
 */

/*! \file */

#include <isc/base64.h>
#include <isc/buffer.h>
#include <isc/region.h>
#include <isc/result.h>

#include <isccc/base64.h>
#include <isccc/result.h>
#include <isccc/util.h>

isc_result_t
isccc_base64_encode(isccc_region_t *source, int wordlength,
		    const char *wordbreak, isccc_region_t *target) {
	isc_region_t sr;
	isc_buffer_t tb;
	isc_result_t result;

	sr.base = source->rstart;
	sr.length = (unsigned int)(source->rend - source->rstart);
	isc_buffer_init(&tb, target->rstart,
			(unsigned int)(target->rend - target->rstart));

	result = isc_base64_totext(&sr, wordlength, wordbreak, &tb);
	if (result != ISC_R_SUCCESS) {
		return (result);
	}
	source->rstart = source->rend;
	target->rstart = isc_buffer_used(&tb);
	return (ISC_R_SUCCESS);
}

isc_result_t
isccc_base64_decode(const char *cstr, isccc_region_t *target) {
	isc_buffer_t b;
	isc_result_t result;

	isc_buffer_init(&b, target->rstart,
			(unsigned int)(target->rend - target->rstart));
	result = isc_base64_decodestring(cstr, &b);
	if (result != ISC_R_SUCCESS) {
		return (result);
	}
	target->rstart = isc_buffer_used(&b);
	return (ISC_R_SUCCESS);
}
