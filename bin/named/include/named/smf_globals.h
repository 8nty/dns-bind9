/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef NAMED_SMF_GLOBALS_H
#define NAMED_SMF_GLOBALS_H 1

#include <libscf.h>

#undef EXTERN
#undef INIT
#ifdef NAMED_MAIN
#define EXTERN
#define INIT(v) = (v)
#else /* ifdef NAMED_MAIN */
#define EXTERN extern
#define INIT(v)
#endif /* ifdef NAMED_MAIN */

EXTERN unsigned int named_smf_got_instance INIT(0);
EXTERN unsigned int named_smf_chroot	   INIT(0);
EXTERN unsigned int named_smf_want_disable INIT(0);

isc_result_t
named_smf_add_message(isc_buffer_t **text);
isc_result_t
named_smf_get_instance(char **name, int debug, isc_mem_t *mctx);

#undef EXTERN
#undef INIT

#endif /* NAMED_SMF_GLOBALS_H */
