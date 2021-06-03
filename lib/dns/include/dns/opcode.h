/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef DNS_OPCODE_H
#define DNS_OPCODE_H 1

/*! \file dns/opcode.h */

#include <isc/lang.h>

#include <dns/types.h>

ISC_LANG_BEGINDECLS

isc_result_t
dns_opcode_totext(dns_opcode_t opcode, isc_buffer_t *target);
/*%<
 * Put a textual representation of error 'opcode' into 'target'.
 *
 * Requires:
 *\li	'opcode' is a valid opcode.
 *
 *\li	'target' is a valid text buffer.
 *
 * Ensures:
 *\li	If the result is success:
 *		The used space in 'target' is updated.
 *
 * Returns:
 *\li	#ISC_R_SUCCESS			on success
 *\li	#ISC_R_NOSPACE			target buffer is too small
 */

ISC_LANG_ENDDECLS

#endif /* DNS_OPCODE_H */
