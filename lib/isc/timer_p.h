/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

#include <isc/mem.h>
#include <isc/result.h>
#include <isc/timer.h>

isc_result_t
isc__timermgr_create(isc_mem_t *mctx, isc_timermgr_t **managerp);
/*%<
 * Create a timer manager.
 *
 * Notes:
 *
 *\li	All memory will be allocated in memory context 'mctx'.
 *
 * Requires:
 *
 *\li	'mctx' is a valid memory context.
 *
 *\li	'managerp' points to a NULL isc_timermgr_t.
 *
 * Ensures:
 *
 *\li	'*managerp' is a valid isc_timermgr_t.
 *
 * Returns:
 *
 *\li	Success
 *\li	No memory
 *\li	Unexpected error
 */

void
isc__timermgr_destroy(isc_timermgr_t **managerp);
/*%<
 * Destroy a timer manager.
 *
 * Notes:
 *
 *\li	This routine blocks until there are no timers left in the manager,
 *	so if the caller holds any timer references using the manager, it
 *	must detach them before calling isc_timermgr_destroy() or it will
 *	block forever.
 *
 * Requires:
 *
 *\li	'*managerp' is a valid isc_timermgr_t.
 *
 * Ensures:
 *
 *\li	*managerp == NULL
 *
 *\li	All resources used by the manager have been freed.
 */
