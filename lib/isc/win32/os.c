/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#include <windows.h>

#include <isc/os.h>

static BOOL bInit = FALSE;
static SYSTEM_INFO SystemInfo;

static void
initialize_action(void) {
	if (bInit) {
		return;
	}

	GetSystemInfo(&SystemInfo);
	bInit = TRUE;
}

unsigned int
isc_os_ncpus(void) {
	long ncpus;
	initialize_action();
	ncpus = SystemInfo.dwNumberOfProcessors;
	if (ncpus <= 0) {
		ncpus = 1;
	}

	return ((unsigned int)ncpus);
}
