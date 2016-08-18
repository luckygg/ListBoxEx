#pragma once

//----------------------------------------------------------
// ScrollbarEx Control
//----------------------------------------------------------
// Programmed by William Kim
//----------------------------------------------------------

#define TIMER_MOUSE_OVER_BUTTON		1	// mouse is over an arrow button, and left button is down
#define TIMER_LBUTTON_PRESSED		2	// mouse is over an arrow button, and left button has just been pressed
#define TIMER_MOUSE_OVER_THUMB		3	// mouse is over thumb
#define TIMER_MOUSE_HOVER_BUTTON	4	// mouse is over an arrow button
#define MOUSE_OVER_BUTTON_TIME		50

#define SIZE_WIDTH  20
#define SIZE_HEIGHT 20
// CScrollBarEx

class CScrollBarEx : public CScrollBar
{
	DECLARE_DYNAMIC(CScrollBarEx)

public:
	CScrollBarEx();
	virtual ~CScrollBarEx();

public :
	//----- Dynamic Create Control -----//
	BOOL CreateContol(CWnd* pWnd, bool bHorizontal, CRect rcSize, UINT ID);

	//----- Init Control -----//
	BOOL InitControl(CWnd* pWnd, bool bHorizontal = true);

	//----- Set Enable & Disable Control -----//
	void SetEnable(bool bEnable) { m_bEnable = bEnable; EnableWindow(bEnable); Invalidate(); }

	//----- Set Color -----//
	void SetColorChannel(int nA, int nR, int nG, int nB) { m_clrChannel = Color(nA, nR, nG, nB); OnInitScrollbar();  }
	void SetColorThumb(int nNomA, int nNomR, int nNomG, int nNomB, int nHiA, int nHiR, int nHiG, int nHiB) { 
		m_clrThumb = Color(nNomA, nNomR, nNomG, nNomB); m_clrThumbHi = Color(nHiA, nHiR, nHiG, nHiB); OnInitScrollbar(); }
	void SetColorArrow(int nNomA, int nNomR, int nNomG, int nNomB, int nHiA, int nHiR, int nHiG, int nHiB) { 
		m_clrArrow = Color(nNomA, nNomR, nNomG, nNomB); m_clrArrowHi = Color(nHiA, nHiR, nHiG, nHiB); OnInitScrollbar(); }
	void SetColorArrowBox(int nNomA, int nNomR, int nNomG, int nNomB, int nHiA, int nHiR, int nHiG, int nHiB) { 
		m_clrArrowBox = Color(nNomA, nNomR, nNomG, nNomB); m_clrArrowBoxHi = Color(nHiA, nHiR, nHiG, nHiB); OnInitScrollbar(); }

	//----- Pos & Range -----//
	int	GetScrollPos() const { return m_nPos; }
	int	SetScrollPos(int nPos, BOOL bRedraw = TRUE);
	void SetScrollRange(int nMinPos, int nMaxPos, BOOL bRedraw = TRUE);

private :
	CWnd *	m_pParent;				// control parent 
	BOOL	m_bThumbHover;			// TRUE = mouse is over thumb
	BOOL	m_bMouseOverArrowRight;	// TRUE = mouse over right arrow
	BOOL	m_bMouseOverArrowLeft;	// TRUE = mouse over left arrow
	BOOL	m_bMouseOverArrowUp;	// TRUE = mouse over up arrow
	BOOL	m_bMouseOverArrowDown;	// TRUE = mouse over down arrow
	BOOL	m_bMouseDownArrowRight;	// TRUE = mouse over right arrow & left button down
	BOOL	m_bMouseDownArrowLeft;	// TRUE = mouse over left arrow & left button down
	BOOL	m_bMouseDownArrowUp;	// TRUE = mouse over up arrow & left button down
	BOOL	m_bMouseDownArrowDown;	// TRUE = mouse over down arrow & left button down
	BOOL	m_bMouseDown;			// TRUE = mouse over thumb & left button down
	BOOL	m_bDragging;			// TRUE = thumb is being dragged
	BOOL	m_bHorizontal;			// TRUE = horizontal scroll bar
	bool	m_bEnable;
	
	int		m_nThumbLeft;			// left margin of thumb
	int		m_nThumbTop;			// top margin of thumb
	int		m_nBitmapHeight;		// height of arrow and thumb bitmaps
	int		m_nBitmapWidth;			// width of arrow and thumb bitmaps
	int		m_nPos;					// current thumb position in scroll units
	int		m_nMinPos;				// minimum scrolling position
	int		m_nMaxPos;				// maximum scrolling position
	int		m_nRange;				// absolute value of max - min pos
	CRect	m_rcThumb;				// current rect for thumb
	CRect	m_rcClient;				// control client rect
	CRect	m_rcLeftArrow;			// left arrow rect
	CRect	m_rcRightArrow;			// right arrow rect
	CRect	m_rcUpArrow;			// up arrow rect
	CRect	m_rcDownArrow;			// down arrow rect

	Color m_clrThumb;				// Thumb ����.
	Color m_clrThumbHi;				// Thumb �� ������ �� ����.
	Color m_clrArrow;				// ȭ��ǥ ����.
	Color m_clrArrowHi;				// ȭ��ǥ ��ư�� ������ �� ȭ��ǥ ����.
	Color m_clrArrowBox;			// ȭ��ǥ ��ư ����.
	Color m_clrArrowBoxHi;			// ȭ��ǥ ��ư�� ������ �� ����.
	Color m_clrChannel;				// ���� �� ����.
	
	Bitmap* m_pBmpThumb;			// Thumb �̹���.	
	Bitmap* m_pBmpThumbHi;			// Thumb �� ������ �� �̹���.
	Bitmap* m_pBmpChannel;			// ���� �� �̹���.
	Bitmap* m_pBmpLeftArrow;		// ���� ȭ��ǥ �̹���.
	Bitmap* m_pBmpLeftArrowHi;		// ���� ȭ��ǥ ���� �̹���.
	Bitmap* m_pBmpRightArrow;		// ������ ȭ��ǥ �̹���.
	Bitmap* m_pBmpRightArrowHi;		// ������ ȭ��ǥ ���� �̹���.
	Bitmap* m_pBmpDownArrow;		// �Ʒ� ȭ��ǥ �̹���.
	Bitmap* m_pBmpDownArrowHi;		// �Ʒ� ȭ��ǥ ���� �̹���.
	Bitmap* m_pBmpUpArrow;			// �� ȭ��ǥ �̹���.
	Bitmap* m_pBmpUpArrowHi;		// �� ȭ��ǥ ���� �̹���.
	
	BOOL CreateFromWindow(DWORD dwStyle,CWnd* pParentWnd,HWND hStatic,UINT nId);
	BOOL CreateFromWindow(DWORD dwStyle,CWnd* pParentWnd,CRect rcRect,UINT nId);
	BOOL CreateFromRect(DWORD dwStyle,CWnd* pParentWnd,CRect& rect,UINT nId);
	
	void OnInitScrollbar();			// ��ũ�ѹٸ� �����ϴ� �̹������� �ҷ����� �Լ�. (�Ǵ� �׸��� �κ�.)
	void LimitThumbPosition();		// ��ũ�ѹ��� ���� ���� ���� ����.
	void SetPositionFromThumb();	// Thumb ��ġ ���� ���.		
	void UpdateThumbPosition();		// Thumb ��ġ ���� ���.
	void ScrollLeft();
	void ScrollRight();
	void ScrollUp();
	void ScrollDown();
	
	void Draw(Graphics* pG);
	void DrawHorizontal(Graphics* pG);
	void DrawVertical(Graphics* pG);

	void OnDeleteBitmaps();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


