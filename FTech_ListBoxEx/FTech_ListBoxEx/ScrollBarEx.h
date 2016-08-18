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

	Color m_clrThumb;				// Thumb 색상.
	Color m_clrThumbHi;				// Thumb 가 눌렸을 때 색상.
	Color m_clrArrow;				// 화살표 색상.
	Color m_clrArrowHi;				// 화살표 버튼이 눌렸을 때 화살표 색상.
	Color m_clrArrowBox;			// 화살표 버튼 색상.
	Color m_clrArrowBoxHi;			// 화살표 버튼이 눌렸을 때 색상.
	Color m_clrChannel;				// 막대 바 색상.
	
	Bitmap* m_pBmpThumb;			// Thumb 이미지.	
	Bitmap* m_pBmpThumbHi;			// Thumb 가 눌렸을 때 이미지.
	Bitmap* m_pBmpChannel;			// 막대 바 이미지.
	Bitmap* m_pBmpLeftArrow;		// 왼쪽 화살표 이미지.
	Bitmap* m_pBmpLeftArrowHi;		// 왼쪽 화살표 눌린 이미지.
	Bitmap* m_pBmpRightArrow;		// 오른쪽 화살표 이미지.
	Bitmap* m_pBmpRightArrowHi;		// 오른족 화살표 눌린 이미지.
	Bitmap* m_pBmpDownArrow;		// 아래 화살표 이미지.
	Bitmap* m_pBmpDownArrowHi;		// 아래 화살표 눌린 이미지.
	Bitmap* m_pBmpUpArrow;			// 위 화살표 이미지.
	Bitmap* m_pBmpUpArrowHi;		// 위 화살표 눌린 이미지.
	
	BOOL CreateFromWindow(DWORD dwStyle,CWnd* pParentWnd,HWND hStatic,UINT nId);
	BOOL CreateFromWindow(DWORD dwStyle,CWnd* pParentWnd,CRect rcRect,UINT nId);
	BOOL CreateFromRect(DWORD dwStyle,CWnd* pParentWnd,CRect& rect,UINT nId);
	
	void OnInitScrollbar();			// 스크롤바를 구성하는 이미지들을 불러오는 함수. (또는 그리는 부분.)
	void LimitThumbPosition();		// 스크롤바의 동작 범위 제한 설정.
	void SetPositionFromThumb();	// Thumb 위치 지정 계산.		
	void UpdateThumbPosition();		// Thumb 위치 지정 계산.
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


