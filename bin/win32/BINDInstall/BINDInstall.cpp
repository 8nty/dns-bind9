/*
 * Copyright (c) 1999-2000 by Nortel Networks Corporation
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0 AND ISC
 */

#include "BINDInstall.h"

#include "BINDInstallDlg.h"
#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBINDInstallApp

BEGIN_MESSAGE_MAP(CBINDInstallApp, CWinApp)
//{{AFX_MSG_MAP(CBINDInstallApp)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG
ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBINDInstallApp construction

CBINDInstallApp::CBINDInstallApp() {
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBINDInstallApp object

CBINDInstallApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBINDInstallApp initialization

BOOL
CBINDInstallApp::InitInstance() {
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
#if _MSC_VER < 1300
#ifdef _AFXDLL
	Enable3dControls(); // Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic(); // Call this when linking to MFC statically
#endif
#endif

	CBINDInstallDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK) {
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	} else if (nResponse == IDCANCEL) {
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
