// ListBoxEx.cpp : implementation file
//

#include "stdafx.h"
#include "ListBoxEx.h"


// CListBoxEx

IMPLEMENT_DYNAMIC(CListBoxEx, CListBox)

CListBoxEx::CListBoxEx()
{
	m_bModeOneColor = true;
	m_nTextAlign1 = 0;
	m_nTextAlign2 = 0;
	m_nOffsetTextX = 0;
	m_nOffsetTextY = 0;
	m_fSizeText = 20;
	m_fSizeBorder = 1;

	m_nItemHeight = 35;
	m_clrBkg = Color(255,128,0,0);
	m_clrBorder = Color(255,255,0,0);
	m_clrItemNom1 = Color(255,128,128,128);
	m_clrItemNom2 = Color(255, 64, 64, 64);
	m_clrItemHot = Color(255,128,0,0);
	m_clrTextNom = Color(255,255,255,255);
	m_clrTextHot = Color(255,255,255,255);
}

CListBoxEx::~CListBoxEx()
{
	
}

BEGIN_MESSAGE_MAP(CListBoxEx, CListBox)
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CListBoxEx message handlers

BOOL CListBoxEx::CreateContol(CWnd* pWnd, CRect rcSize, UINT ID)
{
	if (pWnd == NULL) return false;

	return Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL|LBS_OWNERDRAWVARIABLE|LBS_HASSTRINGS, rcSize, pWnd, ID );
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

	return Create(WS_CHILD|WS_VISIBLE|WS_TABSTOP|WS_VSCROLL|LBS_OWNERDRAWVARIABLE|LBS_HASSTRINGS, rect, pWnd, id );
}

int CListBoxEx::AddString(CString strItem)
{
	return ((CListBox*)this)->AddString(strItem);
}

int CListBoxEx::InsertString(int nIndex, CString strItem)
{
	return ((CListBox*)this)->InsertString(nIndex, strItem);
}

void CListBoxEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if ((int)lpDrawItemStruct->itemID < 0)
		return; 

	CString text;
	GetText(lpDrawItemStruct->itemID, text);
	CRect rect = lpDrawItemStruct->rcItem;

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
	RectF rcfCaption((float)rcItem.left+m_nOffsetTextX, (float)rcItem.top+m_nOffsetTextY, (float)rcItem.Width(),(float)rcItem.Height());
	pG->DrawString(strText,strText.GetLength(),&font,rcfCaption,&formatAlign,&brs);
}

BOOL CListBoxEx::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if(zDelta > 0)
		SetTopIndex(GetTopIndex()-1);
	else
		SetTopIndex(GetTopIndex()+1);

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

