/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef NS_NOTIFY_H
#define NS_NOTIFY_H 1

#include <ns/client.h>

/***
 ***	Module Info
 ***/

/*! \file
 * \brief
 *	RFC1996
 *	A Mechanism for Prompt Notification of Zone Changes (DNS NOTIFY)
 */

/***
 ***	Functions.
 ***/

void
ns_notify_start(ns_client_t *client, isc_nmhandle_t *handle);

/*%<
 *	Examines the incoming message to determine appropriate zone.
 *	Returns FORMERR if there is not exactly one question.
 *	Returns REFUSED if we do not serve the listed zone.
 *	Pass the message to the zone module for processing
 *	and returns the return status.
 *
 * Requires
 *\li	client to be valid.
 */

#endif /* NS_NOTIFY_H */
