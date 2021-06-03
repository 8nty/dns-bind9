/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#include <stdio.h>
#include <windows.h>

#include <isc/mem.h>
#include <isc/tls.h>
#include <isc/util.h>

#include "lib_p.h"

/*
 * Called when we enter the DLL
 */
__declspec(dllexport) BOOL WINAPI
	DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
	/*
	 * The DLL is loading due to process initialization or a call to
	 * LoadLibrary.
	 */
	case DLL_PROCESS_ATTACH:
		isc__initialize();
		break;

	/*
	 * The DLL is unloading from a process due to process
	 * termination or a call to FreeLibrary.
	 */
	case DLL_PROCESS_DETACH:
		isc__shutdown();
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;

	default:
		break;
	}
	return (TRUE);
}
