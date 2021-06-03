/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/*! \file */

#include <isc/errno.h>
#include <isc/util.h>

#include "errno2result.h"

isc_result_t
isc_errno_toresult(int err) {
	return (isc___errno2result(err, false, 0, 0));
}
