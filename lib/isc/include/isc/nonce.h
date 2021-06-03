/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

#include <stdlib.h>

#include <isc/lang.h>

/*! \file isc/nonce.h
 * \brief Provides a function for generating an arbitrarily long nonce.
 */

ISC_LANG_BEGINDECLS

void
isc_nonce_buf(void *buf, size_t buflen);
/*!<
 * Fill 'buf', up to 'buflen' bytes, with random data from the
 * crypto provider's random function.
 */

ISC_LANG_ENDDECLS
