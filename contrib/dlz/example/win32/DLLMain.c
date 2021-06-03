/*
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0
 */

#include <signal.h>
#include <windows.h>

/*
 * Called when we enter the DLL
 */
__declspec(dllexport) BOOL WINAPI
	DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
	/*
	 * The DLL is loading due to process
	 * initialization or a call to LoadLibrary.
	 */
	case DLL_PROCESS_ATTACH:
		break;

	/* The attached process creates a new thread.  */
	case DLL_THREAD_ATTACH:
		break;

	/* The thread of the attached process terminates. */
	case DLL_THREAD_DETACH:
		break;

	/*
	 * The DLL is unloading from a process due to
	 * process termination or a call to FreeLibrary.
	 */
	case DLL_PROCESS_DETACH:
		break;

	default:
		break;
	}
	return (TRUE);
}
