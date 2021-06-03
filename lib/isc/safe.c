/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#include <openssl/crypto.h>

#include <isc/safe.h>

int
isc_safe_memequal(const void *s1, const void *s2, size_t len) {
	return (!CRYPTO_memcmp(s1, s2, len));
}

void
isc_safe_memwipe(void *ptr, size_t len) {
	OPENSSL_cleanse(ptr, len);
}
