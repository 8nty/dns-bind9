/*
 * SPDX-FileCopyrightText: Nominum, Inc.
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0 AND ISC
 */

#ifndef ISCCC_EVENTS_H
#define ISCCC_EVENTS_H 1

/*! \file isccc/events.h */

#include <isc/eventclass.h>

/*%
 * Registry of ISCCC event numbers.
 */

#define ISCCC_EVENT_CCMSG (ISC_EVENTCLASS_ISCCC + 0)

#define ISCCC_EVENT_FIRSTEVENT (ISC_EVENTCLASS_ISCCC + 0)
#define ISCCC_EVENT_LASTEVENT  (ISC_EVENTCLASS_ISCCC + 65535)

#endif /* ISCCC_EVENTS_H */
