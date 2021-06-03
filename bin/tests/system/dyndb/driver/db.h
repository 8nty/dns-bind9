/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/*
 * Copyright (C) 2015  Red Hat ; see COPYRIGHT for license
 */

/**
 * Database API implementation.
 */

#pragma once

#include <isc/mem.h>
#include <isc/result.h>

#include <dns/db.h>
#include <dns/name.h>
#include <dns/rdataclass.h>
#include <dns/rdatatype.h>

isc_result_t
create_db(isc_mem_t *mctx, const dns_name_t *origin, dns_dbtype_t type,
	  dns_rdataclass_t rdclass, unsigned int argc, char *argv[],
	  void *driverarg, dns_db_t **dbp);
