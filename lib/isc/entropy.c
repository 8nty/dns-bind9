/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#include <openssl/err.h>
#include <openssl/rand.h>

#include <isc/types.h>
#include <isc/util.h>

#include "entropy_private.h"

void
isc_entropy_get(void *buf, size_t buflen) {
	if (RAND_bytes(buf, buflen) < 1) {
		FATAL_ERROR(__FILE__, __LINE__, "RAND_bytes(): %s",
			    ERR_error_string(ERR_get_error(), NULL));
	}
}
