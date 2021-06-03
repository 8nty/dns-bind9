/*
 * Copyright (c) 1999-2000 by Nortel Networks Corporation
 * SPDX-FileCopyrightText: Internet Systems Consortium, Inc. ("ISC")
 *
 * SPDX-License-Identifier: MPL-2.0 AND ISC
 */

#ifndef DIRBROWSE_H
#define DIRBROWSE_H

class CDirBrowse : public CDialog {
	/* Construction */
      public:
	CDirBrowse(CString initialDir = "\\",
		   CWnd *pParent = NULL); /* standard
					   * constructor
					   */
	CString
	GetSelectedDir() {
		return (m_selectedDir);
	}

	/*{{AFX_DATA(CDirBrowse) */
	enum { IDD = IDD_BROWSE };
	/* NOTE: the ClassWizard will add data members here */
	/*}}AFX_DATA */

	/* ClassWizard generated virtual function overrides */
	/*{{AFX_VIRTUAL(CDirBrowse) */
      protected:
	virtual void
	DoDataExchange(CDataExchange *pDX); /* DDX/DDV support */
					    /*}}AFX_VIRTUAL */

      protected:
	/* Generated message map functions */
	/*{{AFX_MSG(CDirBrowse) */
	virtual BOOL
	OnInitDialog();
	afx_msg void
	OnDblclkDirlist();
	afx_msg void
	OnSelchangeDirlist();
	/*}}AFX_MSG */
	DECLARE_MESSAGE_MAP()

      private:
	CString m_selectedDir;
};

#endif /* ifndef DIRBROWSE_H */
