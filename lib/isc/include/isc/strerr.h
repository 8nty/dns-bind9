/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#pragma once

/*! \file isc/strerr.h */

#include <isc/string.h>

#if defined(strerror_r)
#undef strerror_r
#endif /* if defined(strerror_r) */
#define strerror_r isc_string_strerror_r
