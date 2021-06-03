/*
 * SPDX-FileCopyrightText: Nominum, Inc.
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0 AND ISC
 */

#ifndef ISCCC_RESULT_H
#define ISCCC_RESULT_H 1

/*! \file isccc/result.h */

#include <isc/lang.h>
#include <isc/result.h>
#include <isc/resultclass.h>

#include <isccc/types.h>

/*% Unknown Version */
#define ISCCC_R_UNKNOWNVERSION (ISC_RESULTCLASS_ISCCC + 0)
/*% Syntax Error */
#define ISCCC_R_SYNTAX (ISC_RESULTCLASS_ISCCC + 1)
/*% Bad Authorization */
#define ISCCC_R_BADAUTH (ISC_RESULTCLASS_ISCCC + 2)
/*% Expired */
#define ISCCC_R_EXPIRED (ISC_RESULTCLASS_ISCCC + 3)
/*% Clock Skew */
#define ISCCC_R_CLOCKSKEW (ISC_RESULTCLASS_ISCCC + 4)
/*% Duplicate */
#define ISCCC_R_DUPLICATE (ISC_RESULTCLASS_ISCCC + 5)

#define ISCCC_R_NRESULTS 6 /*%< Number of results */

ISC_LANG_BEGINDECLS

const char *
isccc_result_totext(isc_result_t result);
/*%
 * Convert a isccc_result_t into a string message describing the result.
 */

void
isccc_result_register(void);

ISC_LANG_ENDDECLS

#endif /* ISCCC_RESULT_H */
