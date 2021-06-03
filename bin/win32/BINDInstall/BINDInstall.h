/*
 * Copyright (c) 1999-2000 by Nortel Networks Corporation
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0 AND ISC
 */

#ifndef BINDINSTALL_H
#define BINDINSTALL_H

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif /* ifndef __AFXWIN_H__ */

#include "resource.h" /* main symbols */

class CBINDInstallApp : public CWinApp {
      public:
	CBINDInstallApp();

	/* ClassWizard generated virtual function overrides */
	/*{{AFX_VIRTUAL(CBINDInstallApp) */
      public:
	virtual BOOL
	InitInstance();
	/*}}AFX_VIRTUAL */

	/*{{AFX_MSG(CBINDInstallApp) */
	/* NOTE - the ClassWizard will add and remove member functions here. */
	/*    DO NOT EDIT what you see in these blocks of generated code ! */
	/*}}AFX_MSG */
	DECLARE_MESSAGE_MAP()
};

#endif /* ifndef BINDINSTALL_H */
