/*
 * SPDX-FileCopyrightText: Nominum, Inc.
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0 AND ISC
 */

#ifndef ISCCC_BASE64_H
#define ISCCC_BASE64_H 1

/*! \file isccc/base64.h */

#include <isc/lang.h>

#include <isccc/types.h>

ISC_LANG_BEGINDECLS

/***
 *** Functions
 ***/

isc_result_t
isccc_base64_encode(isccc_region_t *source, int wordlength,
		    const char *wordbreak, isccc_region_t *target);
/*%<
 * Convert data into base64 encoded text.
 *
 * Notes:
 *\li	The base64 encoded text in 'target' will be divided into
 *	words of at most 'wordlength' characters, separated by
 * 	the 'wordbreak' string.  No parentheses will surround
 *	the text.
 *
 * Requires:
 *\li	'source' is a region containing binary data.
 *\li	'target' is a text region containing available space.
 *\li	'wordbreak' points to a null-terminated string of
 *		zero or more whitespace characters.
 */

isc_result_t
isccc_base64_decode(const char *cstr, isccc_region_t *target);
/*%<
 * Decode a null-terminated base64 string.
 *
 * Requires:
 *\li	'cstr' is non-null.
 *\li	'target' is a valid region.
 *
 * Returns:
 *\li	#ISC_R_SUCCESS	-- the entire decoded representation of 'cstring'
 *			   fit in 'target'.
 *\li	#ISC_R_BADBASE64 -- 'cstr' is not a valid base64 encoding.
 *\li	#ISC_R_NOSPACE	-- 'target' is not big enough.
 */

ISC_LANG_ENDDECLS

#endif /* ISCCC_BASE64_H */
