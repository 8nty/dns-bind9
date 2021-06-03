/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

#ifdef HAVE_STDALIGN_H
#include <stdalign.h>
#else /* ifdef HAVE_STDALIGN_H */
#define alignas(x) __attribute__((__aligned__(x)))
#endif /* ifdef HAVE_STDALIGN_H */
