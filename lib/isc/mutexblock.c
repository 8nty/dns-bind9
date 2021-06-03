/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/*! \file */

#include <isc/mutexblock.h>
#include <isc/util.h>

void
isc_mutexblock_init(isc_mutex_t *block, unsigned int count) {
	unsigned int i;

	for (i = 0; i < count; i++) {
		isc_mutex_init(&block[i]);
	}
}

void
isc_mutexblock_destroy(isc_mutex_t *block, unsigned int count) {
	unsigned int i;

	for (i = 0; i < count; i++) {
		isc_mutex_destroy(&block[i]);
	}
}
