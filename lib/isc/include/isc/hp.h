/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 * SPDX-FileCopyrightText: 2014-2016, Pedro Ramalhete, Andreia Correia
 *
 * SPDX-License-Identifier: MPL-2.0 AND BSD-3-Clause
 */

/*
 * Hazard Pointer implementation.
 *
 * This work is based on C++ code available from:
 * https://github.com/pramalhe/ConcurrencyFreaks/
 */

#pragma once

#include <isc/atomic.h>
#include <isc/mem.h>
#include <isc/string.h>
#include <isc/types.h>
#include <isc/util.h>

/*%
 * Hazard pointers are a mechanism for protecting objects in memory
 * from being deleted by other threads while in use. This allows
 * safe lock-free data structures.
 *
 * This is an adaptation of the ConcurrencyFreaks implementation in C.
 * More details available at https://github.com/pramalhe/ConcurrencyFreaks,
 * in the file HazardPointers.hpp.
 */

typedef void(isc_hp_deletefunc_t)(void *);

void
isc_hp_init(int max_threads);
/*%<
 * Initialize hazard pointer constants, isc__hp_max_threads and
 * isc__hp_max_retired. If more threads try to access hp, it
 * will assert. Calling this function repeatedly can be used
 * to increase the limits, but cannot reduce them.
 */

isc_hp_t *
isc_hp_new(isc_mem_t *mctx, size_t max_hps, isc_hp_deletefunc_t *deletefunc);
/*%<
 * Create a new hazard pointer array of size 'max_hps' (or a reasonable
 * default value if 'max_hps' is 0). The function 'deletefunc' will be
 * used to delete objects protected by hazard pointers when it becomes
 * safe to retire them.
 */

void
isc_hp_destroy(isc_hp_t *hp);
/*%<
 * Destroy a hazard pointer array and clean up all objects protected
 * by hazard pointers.
 */

void
isc_hp_clear(isc_hp_t *hp);
/*%<
 * Clear all hazard pointers in the array for the current thread.
 *
 * Progress condition: wait-free bounded (by max_hps)
 */

void
isc_hp_clear_one(isc_hp_t *hp, int ihp);
/*%<
 * Clear a specified hazard pointer in the array for the current thread.
 *
 * Progress condition: wait-free population oblivious.
 */

uintptr_t
isc_hp_protect(isc_hp_t *hp, int ihp, atomic_uintptr_t *atom);
/*%<
 * Protect an object referenced by 'atom' with a hazard pointer for the
 * current thread.
 *
 * Progress condition: lock-free.
 */

uintptr_t
isc_hp_protect_ptr(isc_hp_t *hp, int ihp, atomic_uintptr_t ptr);
/*%<
 * This returns the same value that is passed as ptr, which is sometimes
 * useful.
 *
 * Progress condition: wait-free population oblivious.
 */

uintptr_t
isc_hp_protect_release(isc_hp_t *hp, int ihp, atomic_uintptr_t ptr);
/*%<
 * Same as isc_hp_protect_ptr(), but explicitly uses memory_order_release.
 *
 * Progress condition: wait-free population oblivious.
 */

void
isc_hp_retire(isc_hp_t *hp, uintptr_t ptr);
/*%<
 * Retire an object that is no longer in use by any thread, calling
 * the delete function that was specified in isc_hp_new().
 *
 * Progress condition: wait-free bounded (by the number of threads squared)
 */
