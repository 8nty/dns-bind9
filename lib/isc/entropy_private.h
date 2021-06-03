/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

#include <stdlib.h>

#include <isc/lang.h>

/*! \file isc/entropy_private.h
 * \brief Implements wrapper around CSPRNG cryptographic library calls
 * for getting cryptographically secure pseudo-random numbers.
 *
 * - If OpenSSL is used, it uses RAND_bytes()
 * - If PKCS#11 is used, it uses pkcs_C_GenerateRandom()
 *
 */

ISC_LANG_BEGINDECLS

void
isc_entropy_get(void *buf, size_t buflen);
/*!<
 * \brief Get cryptographically-secure pseudo-random data.
 */

ISC_LANG_ENDDECLS
