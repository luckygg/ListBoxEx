
// FTech_ListBoxExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FTech_ListBoxEx.h"
#include "FTech_ListBoxExDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFTech_ListBoxExDlg dialog



int g_nCount=0;
CFTech_ListBoxExDlg::CFTech_ListBoxExDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFTech_ListBoxExDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_plbTest = NULL;
}

void CFTech_ListBoxExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lbTest);
}

BEGIN_MESSAGE_MAP(CFTech_ListBoxExDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BtnAdd, &CFTech_ListBoxExDlg::OnBnClickedBtnadd)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CFTech_ListBoxExDlg message handlers

BOOL CFTech_ListBoxExDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	BOOL ret = m_lbTest.InitControl(this);
	m_lbTest.SetAlignTextCM();
	m_lbTest.SetColorBkg(255,128,128,128);
	m_lbTest.SetColorItemHot(255,128,0,0);
	m_lbTest.SetColorItemNomal(255,128,128,128,255,64,64,64);
	m_lbTest.SetColorTextHot(255,0,255,0);
	m_lbTest.AddString(L"RED");
	m_lbTest.AddString(L"Second");
	m_lbTest.AddString(L"Third");
	m_lbTest.AddString(L"RED");
	m_lbTest.AddString(L"Green");
	m_lbTest.AddString(L"Blue");
	m_lbTest.AddString(L"Third");
	m_lbTest.SetCurSel(0);

	m_plbTest = new CListBoxEx();
	m_plbTest->CreateContol(this,CRect(10,200,300,300),1001);
	m_plbTest->SetAlignTextCM();
	m_plbTest->SetColorBkg(255,128,128,128);
	m_plbTest->SetColorItemHot(255,128,0,0);
	m_plbTest->SetColorItemNomal(255,128,128,128,255,64,64,64);
	m_plbTest->SetColorTextHot(255,0,255,0);
	m_plbTest->SetSBColorChannel(255,128,0,128);
	m_plbTest->SetSBColorArrow(255,255,255,255,255,128,0,128);
	m_plbTest->SetItemHeight(25);
	m_plbTest->AddString(L"RED");
	m_plbTest->AddString(L"Second");
	m_plbTest->AddString(L"Third");
	m_plbTest->AddString(L"RED");
	m_plbTest->AddString(L"Green");
	m_plbTest->AddString(L"Blue");
	m_plbTest->AddString(L"Third");
	m_plbTest->SetCurSel(0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFTech_ListBoxExDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFTech_ListBoxExDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFTech_ListBoxExDlg::OnBnClickedBtnadd()
{
	CString tmp;
	tmp.Format(L"%d Text",g_nCount++);

	m_lbTest.AddString(tmp);
	m_plbTest->AddString(tmp);
}


void CFTech_ListBoxExDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	if (m_plbTest != NULL)
	{
		m_plbTest->DestroyWindow();
		delete m_plbTest;
		m_plbTest = NULL;
	}
}
