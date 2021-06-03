/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef NS_EVENTS_H
#define NS_EVENTS_H 1

#include <isc/eventclass.h>

/*! \file ns/events.h
 * \brief
 * Registry of NS event numbers.
 */

#define NS_EVENT_CLIENTCONTROL (ISC_EVENTCLASS_NS + 0)
#define NS_EVENT_HOOKASYNCDONE (ISC_EVENTCLASS_NS + 1)

#endif /* NS_EVENTS_H */
