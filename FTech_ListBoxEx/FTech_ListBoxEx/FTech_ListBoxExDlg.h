
// FTech_ListBoxExDlg.h : header file
//

#pragma once

#include "ListBoxEx.h"

// CFTech_ListBoxExDlg dialog
class CFTech_ListBoxExDlg : public CDialogEx
{
// Construction
public:
	CFTech_ListBoxExDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FTECH_LISTBOXEX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBoxEx m_lbTest;
	CListBoxEx* m_plbTest;
	afx_msg void OnBnClickedBtnadd();
	afx_msg void OnDestroy();
};
