/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

#include <isc/netmgr.h>
#include <isc/result.h>
#include <isc/socket.h>
#include <isc/task.h>
#include <isc/timer.h>

typedef struct isc_managers isc_managers_t;

isc_result_t
isc_managers_create(isc_mem_t *mctx, size_t workers, size_t quantum,
		    size_t sockets, isc_nm_t **netmgrp,
		    isc_taskmgr_t **taskmgrp, isc_timermgr_t **timermgrp,
		    isc_socketmgr_t **socketmgrp);

void
isc_managers_destroy(isc_nm_t **netmgrp, isc_taskmgr_t **taskmgrp,
		     isc_timermgr_t **timermgrp, isc_socketmgr_t **socketmgrp);
