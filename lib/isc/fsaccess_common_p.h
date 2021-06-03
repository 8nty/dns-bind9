/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

/*!
 * Shorthand.  Maybe ISC__FSACCESS_PERMISSIONBITS should not even be in
 * <isc/fsaccess.h>.  Could check consistency with sizeof(isc_fsaccess_t)
 * and the number of bits in each function.
 */
#define STEP  (ISC__FSACCESS_PERMISSIONBITS)
#define GROUP (STEP)
#define OTHER (STEP * 2)

isc_result_t
isc__fsaccess_check_bad_bits(isc_fsaccess_t access, bool is_dir);
