/*
 * Copyright (C) Internet Systems Consortium, Inc. ("ISC")
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, you can obtain one at https://mozilla.org/MPL/2.0/.
 *
 * See the COPYRIGHT file distributed with this work for additional
 * information regarding copyright ownership.
 */

#include <stdio.h>
#include <windows.h>

void
isc__mem_initialize(void);
void
isc__mem_shutdown(void);
void
isc__nm_initialize(void);
void
isc__nm_shutdown(void);

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
		/*
		 * Disable DllMain() invocation on Thread creation/destruction
		 */
		DisableThreadLibraryCalls(hinstDLL);
		isc__mem_initialize(); /* priority=101 */
		isc__nm_initialized(); /* priority=200 */
		break;

	/*
	 * The DLL is unloading from a process due to process
	 * termination or a call to FreeLibrary.
	 */
	case DLL_PROCESS_DETACH:
		isc__nm_shutdown();  /* priority=200 */
		isc__mem_shutdown(); /* priority=101 */
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		/*
		 * Calling DllMain when attaching/detaching process has been
		 * disabled.
		 */
		INSIST(0);
		break;

	default:
		break;
	}
	return (TRUE);
}
