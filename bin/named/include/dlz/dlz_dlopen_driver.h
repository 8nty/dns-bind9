/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#ifndef DLZ_DLOPEN_DRIVER_H
#define DLZ_DLOPEN_DRIVER_H

isc_result_t
dlz_dlopen_init(isc_mem_t *mctx);

void
dlz_dlopen_clear(void);
#endif /* ifndef DLZ_DLOPEN_DRIVER_H */
