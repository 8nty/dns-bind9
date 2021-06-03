/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

/*! \file */

#include <isc/util.h>

#include <isccfg/log.h>

/*%
 * When adding a new category, be sure to add the appropriate
 * \#define to <isccfg/log.h>.
 */
LIBISCCFG_EXTERNAL_DATA isc_logcategory_t cfg_categories[] = { { "config", 0 },
							       { NULL, 0 } };

/*%
 * When adding a new module, be sure to add the appropriate
 * \#define to <isccfg/log.h>.
 */
LIBISCCFG_EXTERNAL_DATA isc_logmodule_t cfg_modules[] = {
	{ "isccfg/parser", 0 }, { NULL, 0 }
};

void
cfg_log_init(isc_log_t *lctx) {
	REQUIRE(lctx != NULL);

	isc_log_registercategories(lctx, cfg_categories);
	isc_log_registermodules(lctx, cfg_modules);
}
