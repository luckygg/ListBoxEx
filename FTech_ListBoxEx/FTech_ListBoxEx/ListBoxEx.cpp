// ListBoxEx.cpp : implementation file
//

#include "stdafx.h"
#include "ListBoxEx.h"


// CListBoxEx

IMPLEMENT_DYNAMIC(CListBoxEx, CListBox)

	CListBoxEx::CListBoxEx()
{
	m_bModeOneColor = true;

	m_nTextAlign1	= 0;
	m_nTextAlign2	= 0;
	m_nOffsetTextX	= 0;
	m_nOffsetTextY	= 0;
	m_fSizeText		= 20;
	m_fSizeBorder	= 1;
	m_nItemHeight	= 35;

	m_clrBkg		= Color(255,128,0,0);
	m_clrBorder		= Color(255,255,0,0);
	m_clrItemNom1	= Color(255,128,128,128);
	m_clrItemNom2	= Color(255, 64, 64, 64);
	m_clrItemHot	= Color(255,128,0,0);
	m_clrTextNom	= Color(255,255,255,255);
	m_clrTextHot	= Color(255,255,255,255);

	m_rcSBV			= CRect(0,0,0,0);
	m_pwndSBV		= NULL;
}

CListBoxEx::~CListBoxEx()
{
	if (m_pwndSBV != NULL)
	{
		m_pwndSBV->DestroyWindow();
		delete m_pwndSBV;
		m_pwndSBV = NULL;
	}
}

BEGIN_MESSAGE_MAP(CListBoxEx, CListBox)
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CListBoxEx message handlers

BOOL CListBoxEx::CreateContol(CWnd* pWnd, CRect rcSize, UINT ID)
{
	if (pWnd == NULL) return false;

	// style에서 'WS_VSCROLL'을 사용안한다.
	//BOOL ret = Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL|LBS_OWNERDRAWVARIABLE|LBS_HASSTRINGS|LBS_NOTIFY, rcSize, pWnd, ID );
	BOOL ret = Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|LBS_OWNERDRAWVARIABLE|LBS_HASSTRINGS|LBS_NOTIFY, rcSize, pWnd, ID );

	m_rcSBV = CRect(rcSize.Width()-20,0,rcSize.Width(),rcSize.Height());
	//m_rcSBV = CRect(rcSize.right-31,0,rcSize.right-11,rcSize.Height());

	m_pwndSBV = new CScrollBarEx();
	m_pwndSBV->CreateContol(this,false,m_rcSBV,WM_USER);

	return ret;
}

BOOL CListBoxEx::InitControl(CWnd* pWnd)
{
	if (pWnd == NULL) return false;

	CRect rect;
	GetWindowRect(&rect);
	pWnd->ScreenToClient(&rect);

	UINT id = GetDlgCtrlID();
	BOOL ret = DestroyWindow();
	if (ret == FALSE) return false;

	//ret = Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL|LBS_OWNERDRAWVARIABLE|LBS_HASSTRINGS, rect, pWnd, id );
	ret = Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|LBS_OWNERDRAWVARIABLE|LBS_HASSTRINGS, rect, pWnd, id );

	m_rcSBV = CRect(rect.Width()-20,0,rect.Width(),rect.Height());
	//m_rcSBV = CRect(rect.right-31,0,rect.right-11,rect.Height());

	m_pwndSBV = new CScrollBarEx();
	m_pwndSBV->CreateContol(this,false,m_rcSBV,WM_USER);

	return ret;
}

int CListBoxEx::AddString(CString strItem)
{
	int cntItem = ((CListBox*)this)->AddString(strItem);	// 현재 아이템 개수.
	int numShow = m_rcSBV.Height() / m_nItemHeight;			// 한 화면에 보여지는 아이템 개수.
	if (cntItem > numShow)
	{
		m_pwndSBV->ShowWindow(SW_SHOW);
		m_pwndSBV->SetScrollRange(0,cntItem-numShow);		// 스크롤바의 범위를 지정.
	}
	else
		m_pwndSBV->ShowWindow(SW_HIDE);

	m_pwndSBV->SetScrollPos(0);
	return cntItem;
}

void CListBoxEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	m_pwndSBV->MoveWindow(m_rcSBV);

	if ((int)lpDrawItemStruct->itemID < 0)
		return; 

	CString text;
	GetText(lpDrawItemStruct->itemID, text);
	CRect rect = lpDrawItemStruct->rcItem;

	int cntItem = GetCount();
	int numShow = m_rcSBV.Height() / m_nItemHeight;
	// 스크롤바가 생성되면 List Box의 드로우 영역을 줄인다.
	if (cntItem > numShow)
		rect.right -= 20;

	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	Graphics mainG (lpDrawItemStruct->hDC);

	Color clrText = m_clrTextNom;
	// 선택된 Item 영역 그리는 부분.
	if ((lpDrawItemStruct->itemState & ODS_SELECTED) && (lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		DrawItem(&mainG,rect,m_clrItemHot);
		clrText = m_clrTextHot;
		DrawText(&mainG,rect,text,clrText);
	}

	// 기본 Item 영역 그리는 부분.
	if (!(lpDrawItemStruct->itemState & ODS_SELECTED) && (lpDrawItemStruct->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
		if (m_bModeOneColor == true)
		{
			DrawItem(&mainG,rect,m_clrItemNom1);
		}
		else
		{
			Color clr;
			lpDrawItemStruct->itemID%2 ? clr = m_clrItemNom1 : clr = m_clrItemNom2;
			DrawItem(&mainG,rect,clr);
		}
		DrawText(&mainG,rect,text,clrText);
	}

	// 선택 -> 미선택 Item 영역 그리는 부분.
	if (!(lpDrawItemStruct->itemState & ODS_SELECTED) && (lpDrawItemStruct->itemAction & ODA_SELECT))
	{
		if (m_bModeOneColor == true)
		{
			DrawItem(&mainG,rect,m_clrItemNom1);
		}
		else
		{
			Color clr;
			lpDrawItemStruct->itemID%2 ? clr = m_clrItemNom1 : clr = m_clrItemNom2;
			DrawItem(&mainG,rect,clr);
		}
		DrawText(&mainG,rect,text,clrText);
	}

}

void CListBoxEx::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = m_nItemHeight;
}

void CListBoxEx::DrawBorder(Graphics *pG, CRect rcRect)
{
	Pen pen(Color(255,255,0,0),m_fSizeBorder);

	pG->DrawRectangle(&pen,rcRect.left,rcRect.top,rcRect.Width(),rcRect.Height());
}

void CListBoxEx::DrawItem(Graphics *pG, CRect rcItem, Color clrItem)
{
	SolidBrush brs(clrItem);

	pG->FillRectangle(&brs,rcItem.left,rcItem.top,rcItem.Width(),rcItem.Height());
}

void CListBoxEx::DrawText(Graphics *pG, CRect rcItem, CString strText, Color clrText)
{
	FontFamily fontptroll(L"Arial");
	Gdiplus::Font font(&fontptroll, m_fSizeText, FontStyleRegular, UnitPixel);

	StringFormat formatAlign;
	formatAlign.SetAlignment((Gdiplus::StringAlignment)m_nTextAlign1);		// Left / Center / Right
	formatAlign.SetLineAlignment((Gdiplus::StringAlignment)m_nTextAlign2);	// Top / Middle / Bottom

	SolidBrush brs(clrText);
	RectF rcfCaption((float)rcItem.left+m_nOffsetTextX, (float)rcItem.top+m_nOffsetTextY, (float)rcItem.Width()-20,(float)rcItem.Height());
	pG->DrawString(strText,strText.GetLength(),&font,rcfCaption,&formatAlign,&brs);
}

BOOL CListBoxEx::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if(zDelta > 0)
	{
		SetTopIndex(GetTopIndex()-1);
		m_pwndSBV->SetScrollPos(GetTopIndex()-1);
	}
	else
	{
		SetTopIndex(GetTopIndex()+1);
		m_pwndSBV->SetScrollPos(GetTopIndex()+1);
	}

	return CListBox::OnMouseWheel(nFlags, zDelta, pt);
}

// Control의 배경색 칠하는 곳.
BOOL CListBoxEx::OnEraseBkgnd(CDC* pDC)
{
	Graphics mainG (pDC->GetSafeHdc());
	CRect rect;
	GetClientRect(&rect);

	DrawItem(&mainG,rect,m_clrBkg);

	return TRUE;
}


void CListBoxEx::OnSize(UINT nType, int cx, int cy)
{
	CListBox::OnSize(nType, cx, cy);

	// List Box의 세로길이가 변경되면 스크롤바를 제거 후 재 생성한다.
	// MoveWindow 호출 시 크기 적용이 안되어 윈도우를 재 생성해서 해결 함. 
	if (m_pwndSBV == NULL) return;

	m_pwndSBV->DestroyWindow();
	delete m_pwndSBV;
	m_pwndSBV = NULL;

	m_rcSBV.bottom = cy;
	m_pwndSBV = new CScrollBarEx();
	m_pwndSBV->CreateContol(this,false,m_rcSBV,1000);

	int cntItem = GetCount();
	int numShow = m_rcSBV.Height() / m_nItemHeight;
	if (cntItem > numShow)
	{
		m_pwndSBV->ShowWindow(SW_SHOW);
		m_pwndSBV->SetScrollRange(0,cntItem-numShow);
	}
	else
		m_pwndSBV->ShowWindow(SW_HIDE);
}

void CListBoxEx::OnDestroy()
{
	CListBox::OnDestroy();

	if (m_pwndSBV != NULL)
	{
		m_pwndSBV->DestroyWindow();
		delete m_pwndSBV;
		m_pwndSBV = NULL;
	}
}

void CListBoxEx::SetColorBkg(int nA, COLORREF clrColor)
{
	int r = GetRValue(clrColor);
	int g = GetGValue(clrColor);
	int b = GetBValue(clrColor);

	m_clrBkg = Color(nA, r, g, b); 
	Invalidate();
}

void CListBoxEx::SetColorBorder(int nA, COLORREF clrColor)
{
	int r = GetRValue(clrColor);
	int g = GetGValue(clrColor);
	int b = GetBValue(clrColor);

	m_clrBorder = Color(nA, r, g, b); 
	Invalidate();
}

void CListBoxEx::SetColorTextHot(int nA, COLORREF clrColor)
{
	int r = GetRValue(clrColor);
	int g = GetGValue(clrColor);
	int b = GetBValue(clrColor);

	m_clrTextHot = Color(nA, r, g, b); 
	Invalidate();
}

void CListBoxEx::SetColorTextNormal(int nA, COLORREF clrColor)
{
	int r = GetRValue(clrColor);
	int g = GetGValue(clrColor);
	int b = GetBValue(clrColor);

	m_clrTextNom = Color(nA, r, g, b); 
	Invalidate();
}

void CListBoxEx::SetColorItemHot(int nA, COLORREF clrColor)
{
	int r = GetRValue(clrColor);
	int g = GetGValue(clrColor);
	int b = GetBValue(clrColor);

	m_clrItemHot = Color(nA, r, g, b); 
	Invalidate();
}

void CListBoxEx::SetColorItemNomal(int nA, COLORREF clrColor)
{
	int r = GetRValue(clrColor);
	int g = GetGValue(clrColor);
	int b = GetBValue(clrColor);

	m_clrItemNom1 = Color(nA, r, g, b); 
	Invalidate();
}

void CListBoxEx::SetColorItemNomal(int nA1, COLORREF clrColor1, int nA2, COLORREF clrColor2)
{
	int r1 = GetRValue(clrColor1);
	int g1 = GetGValue(clrColor1);
	int b1 = GetBValue(clrColor1);

	int r2 = GetRValue(clrColor2);
	int g2 = GetGValue(clrColor2);
	int b2 = GetBValue(clrColor2);

	m_clrItemNom1 = Color(nA1, r1, g1, b1); 
	m_clrItemNom2 = Color(nA2, r2, g2, b2); 
	Invalidate();
}
