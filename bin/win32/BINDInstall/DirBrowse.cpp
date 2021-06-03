/*
 * Copyright (c) 1999-2000 by Nortel Networks Corporation
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0 AND ISC
 */

#include "DirBrowse.h"

#include "BINDInstall.h"
#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDirBrowse dialog

CDirBrowse::CDirBrowse(CString initialDir, CWnd *pParent /*=NULL*/)
    : CDialog(CDirBrowse::IDD, pParent) {
	//{{AFX_DATA_INIT(CDirBrowse)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	/* cppcheck-suppress useInitializationList */
	m_selectedDir = initialDir;
}

void
CDirBrowse::DoDataExchange(CDataExchange *pDX) {
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirBrowse)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDirBrowse, CDialog)
//{{AFX_MSG_MAP(CDirBrowse)
ON_LBN_DBLCLK(IDC_DIRLIST, OnDblclkDirlist)
ON_LBN_SELCHANGE(IDC_DIRLIST, OnSelchangeDirlist)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirBrowse message handlers

BOOL
CDirBrowse::OnInitDialog() {
	CDialog::OnInitDialog();

	DlgDirList((LPTSTR)(LPCTSTR)m_selectedDir, IDC_DIRLIST, IDC_CURDIR,
		   DDL_DIRECTORY);

	return TRUE; // return TRUE unless you set the focus to a control
		     // EXCEPTION: OCX Property Pages should return FALSE
}

void
CDirBrowse::OnDblclkDirlist() {
	CListBox *lb = (CListBox *)GetDlgItem(IDC_DIRLIST);
	CString curSel;

	lb->GetText(lb->GetCurSel(), curSel);
	DlgDirList((LPTSTR)(LPCTSTR)curSel, IDC_DIRLIST, IDC_CURDIR,
		   DDL_DIRECTORY);
}

void
CDirBrowse::OnSelchangeDirlist() {
	// TODO: Add your control notification handler code here
}
