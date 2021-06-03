/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef PK11_INTERNAL_H
#define PK11_INTERNAL_H 1

/*! \file pk11/internal.h */

#include <pk11/pk11.h>

ISC_LANG_BEGINDECLS

const char *
pk11_get_lib_name(void);

void *
pk11_mem_get(size_t size);

void
pk11_mem_put(void *ptr, size_t size);

CK_SLOT_ID
pk11_get_best_token(pk11_optype_t optype);

isc_result_t
pk11_numbits(CK_BYTE_PTR data, unsigned int bytecnt, unsigned int *bits);

CK_ATTRIBUTE *
pk11_attribute_first(const pk11_object_t *obj);

CK_ATTRIBUTE *
pk11_attribute_next(const pk11_object_t *obj, CK_ATTRIBUTE *attr);

CK_ATTRIBUTE *
pk11_attribute_bytype(const pk11_object_t *obj, CK_ATTRIBUTE_TYPE type);

ISC_LANG_ENDDECLS

#endif /* PK11_INTERNAL_H */
