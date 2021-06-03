/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_MUTEXBLOCK_H
#define ISC_MUTEXBLOCK_H 1

/*! \file isc/mutexblock.h */

#include <isc/lang.h>
#include <isc/mutex.h>
#include <isc/types.h>

ISC_LANG_BEGINDECLS

void
isc_mutexblock_init(isc_mutex_t *block, unsigned int count);
/*%<
 * Initialize a block of locks.  If an error occurs all initialized locks
 * will be destroyed, if possible.
 *
 * Requires:
 *
 *\li	block != NULL
 *
 *\li	count > 0
 *
 */

void
isc_mutexblock_destroy(isc_mutex_t *block, unsigned int count);
/*%<
 * Destroy a block of locks.
 *
 * Requires:
 *
 *\li	block != NULL
 *
 *\li	count > 0
 *
 *\li	Each lock in the block be initialized via isc_mutex_init() or
 * 	the whole block was initialized via isc_mutex_initblock().
 *
 */

ISC_LANG_ENDDECLS

#endif /* ISC_MUTEXBLOCK_H */
