// SkinScrollbar.cpp : implementation file
//

#include "stdafx.h"
#include "ScrollbarEx.h"

// CScrollBarEx

IMPLEMENT_DYNAMIC(CScrollBarEx, CScrollBar)

CScrollBarEx::CScrollBarEx()
{
	m_pParent = NULL;
	
	m_clrThumb		= Color(255, 51, 51, 51);
	m_clrThumbHi	= Color(255, 62,109,181);
	m_clrArrow		= Color(255,255,255,255);
	m_clrArrowHi	= Color(255,255,255,255);
	m_clrArrowBox	= Color(255, 41, 41, 41);
	m_clrArrowBoxHi	= Color(255, 62,109,181);
	m_clrChannel	= Color(255,219,219,219);
	
	m_bEnable			   = true;
	m_bHorizontal          = TRUE;
	m_bMouseDown           = FALSE;
	m_bMouseOverArrowRight = FALSE;
	m_bMouseOverArrowLeft  = FALSE;
	m_bMouseOverArrowUp    = FALSE;
	m_bMouseOverArrowDown  = FALSE;
	m_bMouseDownArrowLeft  = FALSE;
	m_bMouseDownArrowRight = FALSE;
	m_bMouseDownArrowUp    = FALSE;
	m_bMouseDownArrowDown  = FALSE;
	m_bDragging            = FALSE;
	m_bThumbHover          = FALSE;
	
	m_rcThumb			= CRect(-1,-1,-1,-1);
	m_rcClient			= CRect(-1,-1,-1,-1);
	m_rcLeftArrow		= CRect(-1,-1,-1,-1);
	m_rcRightArrow		= CRect(-1,-1,-1,-1);
	m_rcUpArrow			= CRect(-1,-1,-1,-1);
	m_rcDownArrow		= CRect(-1,-1,-1,-1);

	m_nPos              = 0;
	m_nMinPos           = 0;
	m_nMaxPos           = 0;
	m_nRange            = 0;
	m_nThumbLeft        = 20;
	m_nThumbTop         = 20;
	m_nBitmapWidth      = SIZE_WIDTH;
	m_nBitmapHeight     = SIZE_HEIGHT;

	m_pBmpThumb			= NULL;				
	m_pBmpThumbHi		= NULL;
	m_pBmpChannel		= NULL;
	m_pBmpLeftArrow		= NULL;
	m_pBmpLeftArrowHi	= NULL;
	m_pBmpRightArrow	= NULL;
	m_pBmpRightArrowHi	= NULL;
	m_pBmpDownArrow		= NULL;
	m_pBmpDownArrowHi	= NULL;
	m_pBmpUpArrow		= NULL;
	m_pBmpUpArrowHi		= NULL;
}

CScrollBarEx::~CScrollBarEx()
{	
	OnDeleteBitmaps();
}

BEGIN_MESSAGE_MAP(CScrollBarEx, CScrollBar)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CScrollBarEx message handlers

void CScrollBarEx::OnDeleteBitmaps()
{
	if (m_pBmpThumb != NULL)
	{
		delete m_pBmpThumb;
		m_pBmpThumb = NULL;
	}
	if (m_pBmpThumbHi != NULL)
	{
		delete m_pBmpThumbHi;
		m_pBmpThumbHi = NULL;
	}
	if (m_pBmpChannel != NULL)
	{
		delete m_pBmpChannel;
		m_pBmpChannel = NULL;
	}
	if (m_pBmpLeftArrow != NULL)
	{
		delete m_pBmpLeftArrow;
		m_pBmpLeftArrow = NULL;
	}
	if (m_pBmpLeftArrowHi != NULL)
	{
		delete m_pBmpLeftArrowHi;
		m_pBmpLeftArrowHi = NULL;
	}
	if (m_pBmpRightArrow != NULL)
	{
		delete m_pBmpRightArrow;
		m_pBmpRightArrow = NULL;
	}
	if (m_pBmpRightArrowHi != NULL)
	{
		delete m_pBmpRightArrowHi;
		m_pBmpRightArrowHi = NULL;
	}
	if (m_pBmpDownArrow != NULL)
	{
		delete m_pBmpDownArrow;
		m_pBmpDownArrow = NULL;
	}
	if (m_pBmpDownArrowHi != NULL)
	{
		delete m_pBmpDownArrowHi;
		m_pBmpDownArrowHi = NULL;
	}
	if (m_pBmpUpArrow != NULL)
	{
		delete m_pBmpUpArrow;
		m_pBmpUpArrow = NULL;
	}
	if (m_pBmpUpArrowHi != NULL)
	{
		delete m_pBmpUpArrowHi;
		m_pBmpUpArrowHi = NULL;
	}
}

BOOL CScrollBarEx::CreateContol(CWnd* pWnd, bool bHorizontal, CRect rcSize, UINT ID)
{
	if (pWnd == NULL) return false;

	DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP;

	bHorizontal ? dwStyle |= SBS_HORZ : dwStyle |= SBS_VERT ;

	return CreateFromWindow(dwStyle,pWnd,rcSize,ID);
}

BOOL CScrollBarEx::InitControl(CWnd* pWnd, bool bHorizontal)
{
	if (pWnd == NULL) return false;

	CRect rect;
	GetWindowRect(&rect);
	pWnd->ScreenToClient(&rect);

	UINT id = GetDlgCtrlID();
	BOOL ret = DestroyWindow();
	if (ret == FALSE) return false;

	DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_TABSTOP;

	bHorizontal ? dwStyle |= SBS_HORZ : dwStyle |= SBS_VERT ;

	return CreateFromWindow(dwStyle,pWnd,rect,id);
}

BOOL CScrollBarEx::CreateFromWindow(DWORD dwStyle, CWnd* pParentWnd, CRect rcRect, UINT nId)
{
	ASSERT(pParentWnd);
	ASSERT(IsWindow(pParentWnd->m_hWnd));

	if (rcRect.Width() < SIZE_WIDTH)
	{
		rcRect.right = rcRect.left + SIZE_WIDTH;
	}

	if (rcRect.Height() < SIZE_HEIGHT)
	{
		rcRect.bottom = rcRect.top + SIZE_HEIGHT;
	}

	// hide placeholder window
	//::ShowWindow(hWnd, SW_HIDE);

	return CreateFromRect(dwStyle, pParentWnd, rcRect, nId);
}

BOOL CScrollBarEx::CreateFromWindow(DWORD dwStyle,
	CWnd* pParentWnd,
	HWND hWnd,
	UINT nId)
{
	ASSERT(pParentWnd);
	ASSERT(IsWindow(pParentWnd->m_hWnd));
	ASSERT(::IsWindow(hWnd));

	CRect rect;
	::GetWindowRect(hWnd, &rect);
	pParentWnd->ScreenToClient(&rect);

	if (rect.Width() < SIZE_WIDTH)
	{
		rect.right = rect.left + SIZE_WIDTH;
	}

	if (rect.Height() < SIZE_HEIGHT)
	{
		rect.bottom = rect.top + SIZE_HEIGHT;
	}

	// hide placeholder window
	::ShowWindow(hWnd, SW_HIDE);

	return CreateFromRect(dwStyle, pParentWnd, rect, nId);
}

BOOL CScrollBarEx::CreateFromRect(DWORD dwStyle,
	CWnd* pParentWnd,
	CRect& rect,
	UINT nId)
{
	ASSERT(pParentWnd);
	ASSERT(IsWindow(pParentWnd->m_hWnd));

	m_pParent = pParentWnd;

	m_bHorizontal = (dwStyle & SBS_VERT) ? FALSE : TRUE;

	BOOL bResult = 	CWnd::Create(
		AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, 0, 0, 0),
		_T(""), dwStyle, rect, pParentWnd, nId);

	if (bResult)
	{
		OnInitScrollbar();

		m_nBitmapWidth = SIZE_WIDTH;
		m_nBitmapHeight = SIZE_HEIGHT;

		GetClientRect(&m_rcClient);

		m_rcLeftArrow = CRect(m_rcClient.left, m_rcClient.top, m_rcClient.left + SIZE_WIDTH, m_rcClient.bottom);

		m_rcRightArrow = CRect(m_rcClient.right - SIZE_WIDTH, m_rcClient.top, m_rcClient.right, m_rcClient.bottom);

		m_rcUpArrow = CRect(m_rcClient.left, m_rcClient.top, m_rcClient.right, m_rcClient.top + SIZE_HEIGHT);

		m_rcDownArrow = CRect(m_rcClient.left, m_rcClient.bottom - SIZE_HEIGHT, m_rcClient.right, m_rcClient.bottom);
	}

	return bResult;
}

void CScrollBarEx::OnInitScrollbar()
{
	CClientDC dc(this);

	OnDeleteBitmaps();
	
	m_pBmpThumb			= new Bitmap(SIZE_WIDTH,SIZE_HEIGHT);
	m_pBmpThumbHi		= new Bitmap(SIZE_WIDTH,SIZE_HEIGHT);
	m_pBmpChannel		= new Bitmap(SIZE_WIDTH,SIZE_HEIGHT);
	m_pBmpLeftArrow		= new Bitmap(SIZE_WIDTH,SIZE_HEIGHT);
	m_pBmpLeftArrowHi	= new Bitmap(SIZE_WIDTH,SIZE_HEIGHT);
	m_pBmpRightArrow	= new Bitmap(SIZE_WIDTH,SIZE_HEIGHT);
	m_pBmpRightArrowHi	= new Bitmap(SIZE_WIDTH,SIZE_HEIGHT);
	m_pBmpDownArrow		= new Bitmap(SIZE_WIDTH,SIZE_HEIGHT);
	m_pBmpDownArrowHi	= new Bitmap(SIZE_WIDTH,SIZE_HEIGHT);
	m_pBmpUpArrow		= new Bitmap(SIZE_WIDTH,SIZE_HEIGHT);
	m_pBmpUpArrowHi		= new Bitmap(SIZE_WIDTH,SIZE_HEIGHT);

	Graphics *pG = NULL;
	SolidBrush brs(Color(255,0,0,0));
	
	//Draw bitmap thumb
	pG = Graphics::FromImage(m_pBmpThumb);
	brs.SetColor(m_clrThumb);
	pG->FillRectangle(&brs,0,0,SIZE_WIDTH,SIZE_HEIGHT);

	//Draw bitmap thumb hi
	pG = Graphics::FromImage(m_pBmpThumbHi);
	brs.SetColor(m_clrThumbHi);
	pG->FillRectangle(&brs,0,0,SIZE_WIDTH,SIZE_HEIGHT);

	//Draw bitmap left arrow box
	pG = Graphics::FromImage(m_pBmpLeftArrow);
	brs.SetColor(m_clrArrowBox);
	pG->FillRectangle(&brs,0,0,SIZE_WIDTH,SIZE_HEIGHT);

	//Draw bitmap left arrow
	Point point[3];
	point[0] = Point(13,16);
	point[1] = Point(8,10);
	point[2] = Point(13,5);
	
	brs.SetColor(m_clrArrow);
	pG->FillPolygon(&brs,point,3);

	//Draw bitmap left arrow box hi
	pG = Graphics::FromImage(m_pBmpLeftArrowHi);
	brs.SetColor(m_clrArrowBoxHi);
	pG->FillRectangle(&brs,0,0,SIZE_WIDTH,SIZE_HEIGHT);

	//Draw bitmap arrow hi
	point[0] = Point(13,16);
	point[1] = Point(8,10);
	point[2] = Point(13,5);

	brs.SetColor(m_clrArrowHi);
	pG->FillPolygon(&brs,point,3);

	//Draw bitmap right arrow box
	pG = Graphics::FromImage(m_pBmpRightArrow);
	brs.SetColor(m_clrArrowBox);
	pG->FillRectangle(&brs,0,0,SIZE_WIDTH,SIZE_HEIGHT);

	//Draw bitmap right arrow
	point[0] = Point(7,4);
	point[1] = Point(12,10);
	point[2] = Point(7,15);

	brs.SetColor(m_clrArrow);
	pG->FillPolygon(&brs,point,3);

	//Draw bitmap right arrow box hi
	pG = Graphics::FromImage(m_pBmpRightArrowHi);
	brs.SetColor(m_clrArrowBoxHi);
	pG->FillRectangle(&brs,0,0,SIZE_WIDTH,SIZE_HEIGHT);

	//Draw bitmap right arrow hi
	point[0] = Point(7,4);
	point[1] = Point(12,10);
	point[2] = Point(7,15);

	brs.SetColor(m_clrArrowHi);
	pG->FillPolygon(&brs,point,3);

	//Draw bitmap up arrow box
	pG = Graphics::FromImage(m_pBmpUpArrow);
	brs.SetColor(m_clrArrowBox);
	pG->FillRectangle(&brs,0,0,SIZE_WIDTH,SIZE_HEIGHT);

	//Draw bitmap up arrow
	point[0] = Point(10,6);
	point[1] = Point(5,12);
	point[2] = Point(15,12);

	brs.SetColor(m_clrArrow);
	pG->FillPolygon(&brs,point,3);

	//Draw bitmap up arrow box hi
	pG = Graphics::FromImage(m_pBmpUpArrowHi);
	brs.SetColor(m_clrArrowBoxHi);
	pG->FillRectangle(&brs,0,0,SIZE_WIDTH,SIZE_HEIGHT);

	//Draw bitmap up arrow hi
	point[0] = Point(10,6);
	point[1] = Point(5,12);
	point[2] = Point(15,12);

	brs.SetColor(m_clrArrowHi);
	pG->FillPolygon(&brs,point,3);

	//Draw bitmap down arrow box
	pG = Graphics::FromImage(m_pBmpDownArrow);
	brs.SetColor(m_clrArrowBox);
	pG->FillRectangle(&brs,0,0,SIZE_WIDTH,SIZE_HEIGHT);

	//Draw bitmap down arrow
	point[0] = Point(5,8);
	point[1] = Point(15,8);
	point[2] = Point(10,13);

	brs.SetColor(m_clrArrow);
	pG->FillPolygon(&brs,point,3);

	//Draw bitmap down arrow box hi
	pG = Graphics::FromImage(m_pBmpDownArrowHi);
	brs.SetColor(m_clrArrowBoxHi);
	pG->FillRectangle(&brs,0,0,SIZE_WIDTH,SIZE_HEIGHT);

	//Draw bitmap down arrow hi
	point[0] = Point(5,8);
	point[1] = Point(15,8);
	point[2] = Point(10,13);

	brs.SetColor(m_clrArrowHi);
	pG->FillPolygon(&brs,point,3);

	//Draw bitmap channel
	pG = Graphics::FromImage(m_pBmpChannel);
	brs.SetColor(m_clrChannel);
	pG->FillRectangle(&brs,0,0,SIZE_WIDTH,SIZE_HEIGHT);
}

BOOL CScrollBarEx::OnEraseBkgnd(CDC* pDC)
{
	//return CWnd::OnEraseBkgnd(pDC);
	return TRUE;
}

void CScrollBarEx::ScrollLeft()
{
	if (m_nPos > 0)
		m_nPos--;
	if (m_pParent && ::IsWindow(m_pParent->m_hWnd))
		m_pParent->SendMessage(WM_HSCROLL, MAKELONG(SB_LINELEFT,0), (LPARAM)m_hWnd);
	UpdateThumbPosition();
}

void CScrollBarEx::ScrollRight()
{
	if (m_nPos < m_nRange)
		m_nPos++;
	if (m_pParent && ::IsWindow(m_pParent->m_hWnd))
		m_pParent->SendMessage(WM_HSCROLL, MAKELONG(SB_LINERIGHT,0), (LPARAM)m_hWnd);
	UpdateThumbPosition();
}

void CScrollBarEx::ScrollUp()
{
	if (m_nPos > 0)
		m_nPos--;
	if (m_pParent && ::IsWindow(m_pParent->m_hWnd))
		m_pParent->SendMessage(WM_VSCROLL, MAKELONG(SB_LINEUP,0), (LPARAM)m_hWnd);
	UpdateThumbPosition();
}

void CScrollBarEx::ScrollDown()
{
	if (m_nPos < m_nRange)
		m_nPos++;
	if (m_pParent && ::IsWindow(m_pParent->m_hWnd))
		m_pParent->SendMessage(WM_VSCROLL, MAKELONG(SB_LINEDOWN,0), (LPARAM)m_hWnd);
	UpdateThumbPosition();
}

void CScrollBarEx::SetPositionFromThumb()
{
	double dPixels, dMax, dInterval, dPos;

	LimitThumbPosition();
	dMax = m_nRange;

	if (m_bHorizontal)
	{
		dPixels   = m_rcClient.Width() - 3*SIZE_WIDTH;
		dInterval = dMax / dPixels;
		dPos      = dInterval * (m_nThumbLeft - SIZE_WIDTH);
	}
	else
	{
		dPixels   = m_rcClient.Height() - 3*SIZE_HEIGHT;
		dInterval = dMax / dPixels;
		dPos      = dInterval * (m_nThumbTop - SIZE_HEIGHT);
	}

	m_nPos = (int) (dPos + 0.5);
	if (m_nPos < 0)
		m_nPos = 0;
	if (m_nPos > m_nRange)
		m_nPos = m_nRange;
}

void CScrollBarEx::UpdateThumbPosition()
{
	double dPixels, dMax, dInterval, dPos;

	dMax = m_nRange;
	dPos = m_nPos;

	if (m_bHorizontal)
	{
		dPixels   = m_rcClient.Width() - 3*SIZE_WIDTH;
		dInterval = dPixels / dMax;
		double dThumbLeft = dPos * dInterval + 0.5;
		m_nThumbLeft = SIZE_WIDTH + (int)dThumbLeft;
	}
	else
	{
		dPixels   = m_rcClient.Height() - 3*SIZE_HEIGHT;
		dInterval = dPixels / dMax;
		double dThumbTop = dPos * dInterval + 0.5;
		m_nThumbTop = SIZE_HEIGHT + (int)dThumbTop;
	}

	LimitThumbPosition();

	Invalidate();
}

void CScrollBarEx::LimitThumbPosition()
{
	if (m_bHorizontal)
	{
		//if ((m_nThumbLeft + m_nBitmapWidth*2) > (m_rcClient.Width() - m_nBitmapWidth))
		if ((m_nThumbLeft + SIZE_WIDTH) > (m_rcClient.Width() - SIZE_WIDTH))
			m_nThumbLeft = m_rcClient.Width() - 2*SIZE_WIDTH;
			//m_nThumbLeft = m_rcClient.Width() - 3*m_nBitmapWidth;

		if (m_nThumbLeft < (m_rcClient.left + SIZE_WIDTH))
			m_nThumbLeft = m_rcClient.left + SIZE_WIDTH;
	}
	else
	{
		//if ((m_nThumbTop + m_nBitmapHeight*2) > (m_rcClient.Height() - m_nBitmapHeight))
		if ((m_nThumbTop + SIZE_HEIGHT) > (m_rcClient.Height() - SIZE_HEIGHT))
			m_nThumbTop = m_rcClient.Height() - 2*SIZE_HEIGHT;
			//m_nThumbTop = m_rcClient.Height() - 3*m_nBitmapHeight;

		if (m_nThumbTop < (m_rcClient.top + SIZE_HEIGHT))
			m_nThumbTop = m_rcClient.top + SIZE_HEIGHT;
	}
}

void CScrollBarEx::SetScrollRange(int nMinPos, int nMaxPos, BOOL bRedraw /*= TRUE*/)
{
	m_nMinPos = nMinPos;
	m_nMaxPos = nMaxPos;
	if (m_nMinPos < m_nMaxPos)
		m_nRange = m_nMaxPos - m_nMinPos;
	else
		m_nRange = m_nMinPos - m_nMaxPos;

	if (bRedraw)
		Invalidate();

	//return *this;
}

int CScrollBarEx::SetScrollPos(int nPos, BOOL bRedraw /*= TRUE*/)
{
	int nOldPos = m_nPos;

	m_nPos = nPos;

	UpdateThumbPosition();

	if (bRedraw)
		Invalidate();

	return nOldPos;
}

void CScrollBarEx::OnPaint()
{
	CPaintDC dc(this);
	
	Graphics mainG(dc.GetSafeHdc());
	
	CRect rect;
	GetClientRect(&rect);
	Bitmap memBmp(rect.Width(), rect.Height());

	Graphics memG(&memBmp);

	SolidBrush brs(Color(255,0,0,0));
	memG.FillRectangle(&brs,0,0,rect.Width(),rect.Height());
	
	if (m_bHorizontal)
		DrawHorizontal(&memG);
	else
		DrawVertical(&memG);

	if (m_bEnable == true)
		mainG.DrawImage(&memBmp,0,0);
	else
	{
		ColorMatrix GrayMat = {	
			0.30f, 0.30f, 0.30f, 0.00f, 0.00f,
			0.59f, 0.59f, 0.59f, 0.00f, 0.00f,
			0.11f, 0.11f, 0.11f, 0.00f, 0.00f,
			0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
			0.00f, 0.00f, 0.00f, 0.00f, 1.00f	};

			ImageAttributes ia;
			ia.SetColorMatrix(&GrayMat);

			RectF grect; grect.X=0, grect.Y=0; grect.Width = (float)rect.Width(); grect.Height = (float)rect.Height();
			mainG.DrawImage(&memBmp, grect, 0, 0, (float)rect.Width(), (float)rect.Height(), UnitPixel, &ia);
	}
}

void CScrollBarEx::DrawHorizontal(Graphics* pG)
{
	//=====  draw left arrow  =====//
	CRect rectLeft(m_rcLeftArrow);
	if (m_bMouseDownArrowLeft)
		rectLeft.OffsetRect(1, 1);

	if (m_bMouseOverArrowLeft)
		pG->DrawImage(m_pBmpLeftArrowHi,Rect(rectLeft.left, rectLeft.top,rectLeft.Width(), rectLeft.Height()), 0, 0, SIZE_WIDTH, SIZE_HEIGHT, UnitPixel);
	else
		pG->DrawImage(m_pBmpLeftArrow,Rect(rectLeft.left, rectLeft.top,rectLeft.Width(), rectLeft.Height()), 0, 0, SIZE_WIDTH, SIZE_HEIGHT, UnitPixel);

	int nChannelStart = m_rcClient.left + SIZE_WIDTH;
	int nChannelWidth = m_rcClient.Width() - 2*SIZE_WIDTH;

	//=====  draw channel  =====//
	m_rcThumb.left   = m_rcClient.left + m_nThumbLeft;
	m_rcThumb.right  = m_rcThumb.left + SIZE_WIDTH;
	m_rcThumb.top    = m_rcClient.top;
	m_rcThumb.bottom = m_rcThumb.top + m_rcClient.Height();

	CRect rectChannelRight(m_rcThumb.left + SIZE_WIDTH/2, m_rcClient.top, nChannelStart + nChannelWidth, m_rcClient.bottom);
	
	//channel은 source를 1,1로 해야한다. 만약, 다르면 그라데이션 효과가 발생.
	pG->DrawImage(m_pBmpChannel,Rect(rectChannelRight.left, rectChannelRight.top,rectChannelRight.Width(), rectChannelRight.Height()),0,0,1,1,UnitPixel);

	CRect rectChannelLeft(nChannelStart, m_rcClient.top,m_rcThumb.left + SIZE_WIDTH/2, m_rcClient.bottom);

	pG->DrawImage(m_pBmpChannel,Rect(rectChannelLeft.left, rectChannelLeft.top,rectChannelLeft.Width(), rectChannelLeft.Height()),0,0,1,1,UnitPixel);

	//=====  draw right arrow  =====//
	CRect rectRight(m_rcRightArrow);
	
	if (m_bMouseDownArrowRight)
		rectRight.OffsetRect(1, 1);

	if (m_bMouseOverArrowRight)
		pG->DrawImage(m_pBmpRightArrowHi,Rect(rectRight.left, rectRight.top,rectRight.Width(), rectRight.Height()),0,0,SIZE_WIDTH,SIZE_HEIGHT,UnitPixel);
	else
		pG->DrawImage(m_pBmpRightArrow,Rect(rectRight.left, rectRight.top,rectRight.Width(), rectRight.Height()),0,0,SIZE_WIDTH,SIZE_HEIGHT,UnitPixel);

	if (m_nRange)
	{
		//=====  draw thumb  =====//
		if (m_bThumbHover)
			pG->DrawImage(m_pBmpThumbHi,Rect(m_rcThumb.left, m_rcThumb.top,m_rcThumb.Width(), m_rcThumb.Height()),0,0,SIZE_WIDTH,SIZE_HEIGHT,UnitPixel);
		else
			pG->DrawImage(m_pBmpThumb,Rect(m_rcThumb.left, m_rcThumb.top,m_rcThumb.Width(), m_rcThumb.Height()),0,0,SIZE_WIDTH,SIZE_HEIGHT,UnitPixel);
	}
	else
	{
		m_rcThumb = CRect(-1,-1,-1,-1);
	}
}

void CScrollBarEx::DrawVertical(Graphics* pG)
{
	//=====  draw Up arrow  =====//
	CRect rectUp(m_rcUpArrow);
	if (m_bMouseDownArrowUp)
		rectUp.OffsetRect(1, 1);

	if (m_bMouseOverArrowUp)
		pG->DrawImage(m_pBmpUpArrowHi,Rect(rectUp.left, rectUp.top,rectUp.Width(), rectUp.Height()),0,0,SIZE_WIDTH,SIZE_HEIGHT,UnitPixel);
	else
		pG->DrawImage(m_pBmpUpArrow,Rect(rectUp.left, rectUp.top,rectUp.Width(), rectUp.Height()),0,0,SIZE_WIDTH,SIZE_HEIGHT,UnitPixel);

	int nChannelStart = m_rcClient.top + SIZE_HEIGHT;
	int nChannelHeight = m_rcClient.Height() - 2*SIZE_HEIGHT;

	//=====  draw channel  =====//
	m_rcThumb.left   = m_rcClient.left;
	m_rcThumb.right  = m_rcThumb.left + m_rcClient.Width();
	m_rcThumb.top    = m_rcClient.top + m_nThumbTop;
	m_rcThumb.bottom = m_rcThumb.top + SIZE_HEIGHT;

	CRect rectChannelDown(m_rcClient.left, m_rcThumb.top + SIZE_HEIGHT/2, m_rcClient.right, nChannelStart + nChannelHeight);
	
	//channel은 source를 1,1로 해야한다. 만약, 다르면 그라데이션 효과가 발생.
	pG->DrawImage(m_pBmpChannel,Rect(rectChannelDown.left, rectChannelDown.top,rectChannelDown.Width(), rectChannelDown.Height()),0,0,1,1,UnitPixel);

	CRect rectChannelUp(m_rcClient.left, nChannelStart, m_rcClient.right, m_rcThumb.top + SIZE_HEIGHT/2);

	pG->DrawImage(m_pBmpChannel,Rect(rectChannelUp.left, rectChannelUp.top,rectChannelUp.Width(), rectChannelUp.Height()),0,0,1,1,UnitPixel);

	// =====  draw down arrow  =====

	CRect rectDown(m_rcDownArrow);
	if (m_bMouseDownArrowDown)
		rectDown.OffsetRect(1, 1);

	if (m_bMouseOverArrowDown)
		pG->DrawImage(m_pBmpDownArrowHi,Rect(rectDown.left, rectDown.top,rectDown.Width(), rectDown.Height()),0,0,SIZE_WIDTH,SIZE_HEIGHT,UnitPixel);
	else
		pG->DrawImage(m_pBmpDownArrow,Rect(rectDown.left, rectDown.top,rectDown.Width(), rectDown.Height()),0,0,SIZE_WIDTH,SIZE_HEIGHT,UnitPixel);

	// if there is nothing to scroll then don't show the thumb
	if (m_nRange)
	{
		if (m_bThumbHover)
			pG->DrawImage(m_pBmpThumbHi,Rect(m_rcThumb.left, m_rcThumb.top,m_rcThumb.Width(), m_rcThumb.Height()),0,0,SIZE_WIDTH,SIZE_HEIGHT,UnitPixel);
		else
			pG->DrawImage(m_pBmpThumb,Rect(m_rcThumb.left, m_rcThumb.top,m_rcThumb.Width(), m_rcThumb.Height()),0,0,SIZE_WIDTH,SIZE_HEIGHT,UnitPixel);
	}
	else
	{
		m_rcThumb = CRect(-1,-1,-1,-1);
	}
}

void CScrollBarEx::OnLButtonDown(UINT nFlags, CPoint point)
{
	KillTimer(TIMER_MOUSE_OVER_BUTTON);
	KillTimer(TIMER_LBUTTON_PRESSED);
	SetCapture();
	SetFocus();

	if (m_bHorizontal)
	{
		m_bMouseDownArrowLeft = FALSE;
		m_bMouseDownArrowRight = FALSE;
		
		CRect rectThumb(m_nThumbLeft, 0, m_nThumbLeft + SIZE_WIDTH,m_rcClient.Height());

		if (rectThumb.PtInRect(point))
		{
			m_bMouseDown = TRUE;
		}
		else if (m_rcRightArrow.PtInRect(point))
		{
			m_bMouseDownArrowRight = TRUE;
			SetTimer(TIMER_LBUTTON_PRESSED, 200, NULL);
		}
		else if (m_rcLeftArrow.PtInRect(point))
		{
			m_bMouseDownArrowLeft = TRUE;
			SetTimer(TIMER_LBUTTON_PRESSED, 200, NULL);
		}
		else	// button down in channel
		{
			m_nThumbLeft = point.x - (SIZE_WIDTH) / 2;
			SetPositionFromThumb();

			if (m_pParent && ::IsWindow(m_pParent->m_hWnd))
				m_pParent->SendMessage(WM_HSCROLL, MAKELONG(SB_THUMBTRACK, m_nPos),(LPARAM)m_hWnd);
		}
		Invalidate();
	}
	else
	{
		CRect rectThumb(0, m_nThumbTop, m_rcClient.Width(), m_nThumbTop + SIZE_HEIGHT);

		if (rectThumb.PtInRect(point))
		{
			m_bMouseDown = TRUE;
		}
		else if (m_rcDownArrow.PtInRect(point))
		{
			m_bMouseDownArrowDown = TRUE;
			SetTimer(TIMER_LBUTTON_PRESSED, 150, NULL);
		}
		else if (m_rcUpArrow.PtInRect(point))
		{
			m_bMouseDownArrowUp = TRUE;
			SetTimer(TIMER_LBUTTON_PRESSED, 150, NULL);
		}
		else	// button down in channel
		{
			m_nThumbTop = point.y - (SIZE_HEIGHT) / 2;
			SetPositionFromThumb();

			if (m_pParent && ::IsWindow(m_pParent->m_hWnd))
				m_pParent->SendMessage(WM_VSCROLL, MAKELONG(SB_THUMBTRACK, m_nPos), (LPARAM)m_hWnd);
		}
		Invalidate();
	}
	CWnd::OnLButtonDown(nFlags, point);
}


void CScrollBarEx::OnLButtonUp(UINT nFlags, CPoint point)
{
	UpdateThumbPosition();
	KillTimer(TIMER_MOUSE_OVER_BUTTON);
	KillTimer(TIMER_LBUTTON_PRESSED);
	ReleaseCapture();

	if (m_bHorizontal)
	{
		CRect rectThumb(m_nThumbLeft, 0, m_nThumbLeft + SIZE_WIDTH, m_rcClient.Height());

		m_bMouseDownArrowLeft = FALSE;
		m_bMouseDownArrowRight = FALSE;

		if (m_rcLeftArrow.PtInRect(point))
		{
			ScrollLeft();
		}
		else if (m_rcRightArrow.PtInRect(point))
		{
			ScrollRight();
		}
		else if (rectThumb.PtInRect(point))
		{
			m_bThumbHover = TRUE;
			SetTimer(TIMER_MOUSE_OVER_THUMB, 50, NULL);
		}
		Invalidate();
	}
	else
	{
		CRect rectThumb(0, m_nThumbTop, m_rcClient.Width(), m_nThumbTop + SIZE_HEIGHT);

		m_bMouseDownArrowUp = FALSE;
		m_bMouseDownArrowDown = FALSE;

		if (m_rcUpArrow.PtInRect(point))
		{
			ScrollUp();
		}
		else if (m_rcDownArrow.PtInRect(point))
		{
			ScrollDown();
		}
		else if (rectThumb.PtInRect(point))
		{
			m_bThumbHover = TRUE;
			SetTimer(TIMER_MOUSE_OVER_THUMB, 50, NULL);
		}
		Invalidate();
	}

	m_bMouseDown = FALSE;
	m_bDragging = FALSE;

	CWnd::OnLButtonUp(nFlags, point);
}

void CScrollBarEx::OnMouseMove(UINT nFlags, CPoint point)
{
	BOOL bOldThumbHover = m_bThumbHover;
	m_bThumbHover = FALSE;

	if (m_rcThumb.PtInRect(point))
		m_bThumbHover = TRUE;

	if (m_bMouseDown)
		m_bDragging = TRUE;

	BOOL bOldHover = m_bMouseOverArrowRight |
		m_bMouseOverArrowLeft  |
		m_bMouseOverArrowUp    |
		m_bMouseOverArrowDown;

	m_bMouseOverArrowRight = FALSE;
	m_bMouseOverArrowLeft  = FALSE;
	m_bMouseOverArrowUp    = FALSE;
	m_bMouseOverArrowDown  = FALSE;

	if (m_bHorizontal)
	{
		if (m_rcLeftArrow.PtInRect(point))
			m_bMouseOverArrowLeft = TRUE;
		else if (m_rcRightArrow.PtInRect(point))
			m_bMouseOverArrowRight = TRUE;
	}
	else
	{
		if (m_rcUpArrow.PtInRect(point))
			m_bMouseOverArrowUp = TRUE;
		else if (m_rcDownArrow.PtInRect(point))
			m_bMouseOverArrowDown = TRUE;
	}

	BOOL bNewHover = m_bMouseOverArrowRight |
		m_bMouseOverArrowLeft  |
		m_bMouseOverArrowUp    |
		m_bMouseOverArrowDown;

	if (bNewHover)
		SetTimer(TIMER_MOUSE_HOVER_BUTTON, 80, NULL);

	if (bOldHover != bNewHover)
		Invalidate();

	if (m_bDragging)
	{
		if (m_bHorizontal)
		{
			m_nThumbLeft = point.x - (SIZE_WIDTH) / 2;

			SetPositionFromThumb();

			if (m_pParent && ::IsWindow(m_pParent->m_hWnd))
				m_pParent->SendMessage(WM_HSCROLL, MAKELONG(SB_THUMBTRACK, m_nPos), (LPARAM)m_hWnd);
		}
		else
		{
			m_nThumbTop = point.y - (SIZE_HEIGHT) / 2;
			SetPositionFromThumb();
			if (m_pParent && ::IsWindow(m_pParent->m_hWnd))
				m_pParent->SendMessage(WM_VSCROLL, MAKELONG(SB_THUMBTRACK, m_nPos), (LPARAM)m_hWnd);
		}

		Invalidate();
	}

	if (bOldThumbHover != m_bThumbHover)
	{
		Invalidate();
		SetTimer(TIMER_MOUSE_OVER_THUMB, 50, NULL);
	}

	CWnd::OnMouseMove(nFlags, point);
}


void CScrollBarEx::OnTimer(UINT_PTR nIDEvent)
{
	CPoint point;
	::GetCursorPos(&point);
	ScreenToClient(&point);

	CRect rect;
	GetWindowRect(&rect);
	ScreenToClient(&rect);

	if (nIDEvent == TIMER_MOUSE_HOVER_BUTTON)
	{
		m_bMouseOverArrowRight = FALSE;
		m_bMouseOverArrowLeft  = FALSE;
		m_bMouseOverArrowUp    = FALSE;
		m_bMouseOverArrowDown  = FALSE;

		if (m_bHorizontal)
		{
			if (m_rcLeftArrow.PtInRect(point))
				m_bMouseOverArrowLeft = TRUE;
			else if (m_rcRightArrow.PtInRect(point))
				m_bMouseOverArrowRight = TRUE;
		}
		else
		{
			if (m_rcUpArrow.PtInRect(point))
				m_bMouseOverArrowUp = TRUE;
			else if (m_rcDownArrow.PtInRect(point))
				m_bMouseOverArrowDown = TRUE;
		}

		if (!m_bMouseOverArrowLeft  &&
			!m_bMouseOverArrowRight && 
			!m_bMouseOverArrowUp    &&
			!m_bMouseOverArrowDown)
		{
			KillTimer(nIDEvent);
			Invalidate();
		}
	}
	else if (nIDEvent == TIMER_MOUSE_OVER_BUTTON)	// mouse is in an arrow button, and left button is down
	{
		if (m_bMouseDownArrowLeft)
			ScrollLeft();
		if (m_bMouseDownArrowRight)
			ScrollRight();
		if (m_bMouseDownArrowUp)
			ScrollUp();
		if (m_bMouseDownArrowDown)
			ScrollDown();

		if (!rect.PtInRect(point))
		{
			m_bMouseDownArrowLeft  = FALSE;
			m_bMouseDownArrowRight = FALSE;
			m_bMouseDownArrowUp    = FALSE;
			m_bMouseDownArrowDown  = FALSE;
		}
		if (!m_bMouseDownArrowLeft  &&
			!m_bMouseDownArrowRight && 
			!m_bMouseDownArrowUp    &&
			!m_bMouseDownArrowDown)
		{
			KillTimer(nIDEvent);
			Invalidate();
		}
	}
	else if (nIDEvent == TIMER_LBUTTON_PRESSED)	// mouse is in an arrow button, and left button has just been pressed
	{
		KillTimer(nIDEvent);

		if (m_bMouseDownArrowLeft  || 
			m_bMouseDownArrowRight || 
			m_bMouseDownArrowUp    || 
			m_bMouseDownArrowDown)
		{
			// debounce left click
			SetTimer(TIMER_MOUSE_OVER_BUTTON, MOUSE_OVER_BUTTON_TIME, NULL);
			Invalidate();
		}
	}
	else if (nIDEvent == TIMER_MOUSE_OVER_THUMB)	// mouse is over thumb
	{
		if (!m_rcThumb.PtInRect(point))
		{
			// no longer over thumb, restore thumb color
			m_bThumbHover = FALSE;
			KillTimer(nIDEvent);
			::SetCursor(::LoadCursor(NULL, IDC_ARROW));
			Invalidate();
		}
	}

	CWnd::OnTimer(nIDEvent);
}
