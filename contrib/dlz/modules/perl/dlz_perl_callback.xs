/*
 * SPDX-FileCopyrightText: 2012  John Eaglesham
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0 AND ISC
 */

#include <dlz_minimal.h>

#include "EXTERN.h"
#include "XSUB.h"
#include "dlz_perl_driver.h"
#include "perl.h"

/* And some XS code. */
MODULE = DLZ_Perl PACKAGE = DLZ_Perl

	int
	LOG_INFO() CODE : RETVAL = ISC_LOG_INFO;
OUTPUT : RETVAL

	 int
	 LOG_NOTICE() CODE : RETVAL = ISC_LOG_NOTICE;
OUTPUT : RETVAL

	 int
	 LOG_WARNING() CODE : RETVAL = ISC_LOG_WARNING;
OUTPUT : RETVAL

	 int
	 LOG_ERROR() CODE : RETVAL = ISC_LOG_ERROR;
OUTPUT : RETVAL

	 int
	 LOG_CRITICAL() CODE : RETVAL = ISC_LOG_CRITICAL;
OUTPUT : RETVAL

	 void log(opaque, level, msg) IV opaque int level char *msg

	 PREINIT : log_t *log = (log_t *)opaque;

CODE : log(level, msg);
