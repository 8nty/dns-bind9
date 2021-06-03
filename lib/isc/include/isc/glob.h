/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_GLOB_H
#define ISC_GLOB_H

#include <isc/lang.h>
#include <isc/result.h>

#if HAVE_GLOB_H
#include <glob.h>
#else
#include <stddef.h>

#include <isc/mem.h>

typedef struct {
	size_t	   gl_pathc;
	char **	   gl_pathv;
	isc_mem_t *mctx;
	void *	   reserved;
} glob_t;

#endif

ISC_LANG_BEGINDECLS

isc_result_t
isc_glob(const char *pattern, glob_t *pglob);

void
isc_globfree(glob_t *pglob);

ISC_LANG_ENDDECLS

#endif /* ISC_GLOB_H */
