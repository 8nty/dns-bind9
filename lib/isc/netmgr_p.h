/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

#include <isc/mem.h>
#include <isc/result.h>

void
isc__netmgr_create(isc_mem_t *mctx, uint32_t workers, isc_nm_t **netgmrp);
/*%<
 * Creates a new network manager with 'workers' worker threads,
 * and starts it running.
 */

void
isc__netmgr_destroy(isc_nm_t **netmgrp);
/*%<
 * Similar to isc_nm_detach(), but actively waits for all other references
 * to be gone before returning.
 */

void
isc__netmgr_shutdown(isc_nm_t *mgr);
/*%<
 * Shut down all active connections, freeing associated resources;
 * prevent new connections from being established.
 */
