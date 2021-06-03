/*
 * SPDX-FileCopyrightText: Nominum, Inc.
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0 AND ISC
 */

#ifndef ISCCC_TYPES_H
#define ISCCC_TYPES_H 1

/*! \file isccc/types.h */

#include <inttypes.h>

#include <isc/result.h>

/*% isccc_time_t typedef */
typedef uint32_t isccc_time_t;

/*% isccc_sexpr_t typedef */
typedef struct isccc_sexpr isccc_sexpr_t;
/*% isccc_dottedpair_t typedef */
typedef struct isccc_dottedpair isccc_dottedpair_t;
/*% isccc_symtab_t typedef */
typedef struct isccc_symtab isccc_symtab_t;

/*% iscc region structure */
typedef struct isccc_region {
	unsigned char *rstart;
	unsigned char *rend;
} isccc_region_t;

#endif /* ISCCC_TYPES_H */
