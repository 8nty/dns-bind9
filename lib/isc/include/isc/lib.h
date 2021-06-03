/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef ISC_LIB_H
#define ISC_LIB_H 1

/*! \file isc/lib.h */

#include <isc/lang.h>
#include <isc/types.h>

ISC_LANG_BEGINDECLS

void
isc_lib_register(void);
/*!<
 * \brief Register the ISC library implementations for some base services
 * such as memory or event management and handling socket or timer events.
 * An external application that wants to use the ISC library must call this
 * function very early in main().
 */

ISC_LANG_ENDDECLS

#endif /* ISC_LIB_H */
