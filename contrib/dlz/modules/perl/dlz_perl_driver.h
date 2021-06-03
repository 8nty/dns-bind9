/*
 * SPDX-FileCopyrightText: 2009-2012  John Eaglesham
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0 AND ISC
 */

#include <dlz_minimal.h>

/* This is the only part that differs from dlz_minimal.h. */
typedef struct dlz_perl_clientinfo_opaque {
	dns_clientinfomethods_t *methods;
	dns_clientinfo_t *clientinfo;
} dlz_perl_clientinfo_opaque;
