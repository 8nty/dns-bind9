/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_ONCE_H
#define ISC_ONCE_H 1

/*! \file */

#include <pthread.h>

#include <isc/platform.h>
#include <isc/result.h>

typedef pthread_once_t isc_once_t;

#define ISC_ONCE_INIT PTHREAD_ONCE_INIT

/* XXX We could do fancier error handling... */

#define isc_once_do(op, f) \
	((pthread_once((op), (f)) == 0) ? ISC_R_SUCCESS : ISC_R_UNEXPECTED)

#endif /* ISC_ONCE_H */
