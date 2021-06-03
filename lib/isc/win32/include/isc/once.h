/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_ONCE_H
#define ISC_ONCE_H 1

#include <isc/lang.h>
#include <isc/result.h>

ISC_LANG_BEGINDECLS

typedef struct {
	int status;
	int counter;
} isc_once_t;

#define ISC_ONCE_INIT_NEEDED 0
#define ISC_ONCE_INIT_DONE   1

#define ISC_ONCE_INIT                   \
	{                               \
		ISC_ONCE_INIT_NEEDED, 1 \
	}

isc_result_t
isc_once_do(isc_once_t *controller, void (*function)(void));

ISC_LANG_ENDDECLS

#endif /* ISC_ONCE_H */
