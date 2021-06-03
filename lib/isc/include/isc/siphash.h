/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/*! \file isc/siphash.h */

#pragma once

#include <isc/lang.h>
#include <isc/platform.h>
#include <isc/types.h>

#define ISC_SIPHASH24_KEY_LENGTH 128 / 8
#define ISC_SIPHASH24_TAG_LENGTH 64 / 8

#define ISC_HALFSIPHASH24_KEY_LENGTH 64 / 8
#define ISC_HALFSIPHASH24_TAG_LENGTH 32 / 8

ISC_LANG_BEGINDECLS

void
isc_siphash24(const uint8_t *key, const uint8_t *in, const size_t inlen,
	      uint8_t *out);
void
isc_halfsiphash24(const uint8_t *key, const uint8_t *in, const size_t inlen,
		  uint8_t *out);

ISC_LANG_ENDDECLS
