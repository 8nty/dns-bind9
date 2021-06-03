/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/*! \file */

#include <inttypes.h>
#include <stdbool.h>

#include <isc/serial.h>

bool
isc_serial_lt(uint32_t a, uint32_t b) {
	/*
	 * Undefined => false
	 */
	if (a == (b ^ 0x80000000U)) {
		return (false);
	}
	return (((int32_t)(a - b) < 0) ? true : false);
}

bool
isc_serial_gt(uint32_t a, uint32_t b) {
	return (((int32_t)(a - b) > 0) ? true : false);
}

bool
isc_serial_le(uint32_t a, uint32_t b) {
	return ((a == b) ? true : isc_serial_lt(a, b));
}

bool
isc_serial_ge(uint32_t a, uint32_t b) {
	return ((a == b) ? true : isc_serial_gt(a, b));
}

bool
isc_serial_eq(uint32_t a, uint32_t b) {
	return ((a == b) ? true : false);
}

bool
isc_serial_ne(uint32_t a, uint32_t b) {
	return ((a != b) ? true : false);
}
