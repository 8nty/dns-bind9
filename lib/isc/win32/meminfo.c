/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#include <inttypes.h>
#include <windows.h>

#include <isc/meminfo.h>

uint64_t
isc_meminfo_totalphys(void) {
	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	return ((uint64_t)statex.ullTotalPhys);
}
