/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef NS_UPDATE_H
#define NS_UPDATE_H 1

/*****
***** Module Info
*****/

/*! \file
 * \brief
 * RFC2136 Dynamic Update
 */

/***
 *** Imports
 ***/

#include <dns/result.h>
#include <dns/types.h>

/***
 *** Types.
 ***/

/***
 *** Functions
 ***/

void
ns_update_start(ns_client_t *client, isc_nmhandle_t *handle,
		isc_result_t sigresult);

#endif /* NS_UPDATE_H */
