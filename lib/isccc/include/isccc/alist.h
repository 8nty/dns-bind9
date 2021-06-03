/*
 * SPDX-FileCopyrightText: Nominum, Inc.
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0 AND ISC
 */

#ifndef ISCCC_ALIST_H
#define ISCCC_ALIST_H 1

/*! \file isccc/alist.h */

#include <stdbool.h>
#include <stdio.h>

#include <isc/lang.h>

#include <isccc/types.h>

ISC_LANG_BEGINDECLS

isccc_sexpr_t *
isccc_alist_create(void);

bool
isccc_alist_alistp(isccc_sexpr_t *alist);

bool
isccc_alist_emptyp(isccc_sexpr_t *alist);

isccc_sexpr_t *
isccc_alist_first(isccc_sexpr_t *alist);

isccc_sexpr_t *
isccc_alist_assq(isccc_sexpr_t *alist, const char *key);

void
isccc_alist_delete(isccc_sexpr_t *alist, const char *key);

isccc_sexpr_t *
isccc_alist_define(isccc_sexpr_t *alist, const char *key, isccc_sexpr_t *value);

isccc_sexpr_t *
isccc_alist_definestring(isccc_sexpr_t *alist, const char *key,
			 const char *str);

isccc_sexpr_t *
isccc_alist_definebinary(isccc_sexpr_t *alist, const char *key,
			 isccc_region_t *r);

isccc_sexpr_t *
isccc_alist_lookup(isccc_sexpr_t *alist, const char *key);

isc_result_t
isccc_alist_lookupstring(isccc_sexpr_t *alist, const char *key, char **strp);

isc_result_t
isccc_alist_lookupbinary(isccc_sexpr_t *alist, const char *key,
			 isccc_region_t **r);

void
isccc_alist_prettyprint(isccc_sexpr_t *sexpr, unsigned int indent,
			FILE *stream);

ISC_LANG_ENDDECLS

#endif /* ISCCC_ALIST_H */
