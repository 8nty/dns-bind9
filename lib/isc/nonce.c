/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#include <isc/nonce.h>

#include "entropy_private.h"

void
isc_nonce_buf(void *buf, size_t buflen) {
	isc_entropy_get(buf, buflen);
}
