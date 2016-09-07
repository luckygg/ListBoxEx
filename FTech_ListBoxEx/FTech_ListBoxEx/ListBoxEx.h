#pragma once

//----------------------------------------------------------
// ListBoxEx Control
//----------------------------------------------------------
// Programmed by William Kim
//----------------------------------------------------------
// Last Update : 2016-09-07 18:50
// Modified by William Kim
//----------------------------------------------------------

#include "ScrollBarEx.h"
// CListBoxEx

class CListBoxEx : public CListBox
{
	DECLARE_DYNAMIC(CListBoxEx)

public:
	CListBoxEx();
	virtual ~CListBoxEx();

public :

	//----- Dynamic Create Control -----//
	BOOL CreateContol(CWnd* pWnd, CRect rcSize, UINT ID);

	//----- Init Control -----//
	BOOL InitControl(CWnd* pWnd);

	//----- Add Item -----//
	int AddString(CString strItem);										

	//----- Set Size -----//
	void SetSizeText	(float fSize) { m_fSizeText		= fSize; }
	void SetSizeBorder	(float fSize) { m_fSizeBorder	= fSize; }
	void SetItemHeight(int nHeight) { m_nItemHeight = nHeight; Invalidate(); }

	//----- Set Color -----//
	void SetColorBkg		(int nA, int nR, int nG, int nB) { m_clrBkg		= Color(nA, nR, nG, nB); Invalidate(); }
	void SetColorBorder		(int nA, int nR, int nG, int nB) { m_clrBorder	= Color(nA, nR, nG, nB); Invalidate(); }
	void SetColorTextHot	(int nA, int nR, int nG, int nB) { m_clrTextHot = Color(nA, nR, nG, nB); Invalidate(); }
	void SetColorTextNormal	(int nA, int nR, int nG, int nB) { m_clrTextNom = Color(nA, nR, nG, nB); Invalidate(); }
	void SetColorItemHot	(int nA, int nR, int nG, int nB) { m_clrItemHot = Color(nA, nR, nG, nB); Invalidate(); }
	void SetColorItemNomal	(int nA, int nR, int nG, int nB) { m_clrItemNom1 = Color(nA, nR, nG, nB); m_bModeOneColor = true; Invalidate(); }
	void SetColorItemNomal	(int nA1, int nR1, int nG1, int nB1, int nA2, int nR2, int nG2, int nB2) { 
		m_clrItemNom1 = Color(nA1, nR1, nG1, nB1); m_clrItemNom2 = Color(nA2, nR2, nG2, nB2); m_bModeOneColor = false; Invalidate(); }
	void SetColorBkg		(int nA, COLORREF clrColor);
	void SetColorBorder		(int nA, COLORREF clrColor);
	void SetColorTextHot	(int nA, COLORREF clrColor);
	void SetColorTextNormal	(int nA, COLORREF clrColor);
	void SetColorItemHot	(int nA, COLORREF clrColor);
	void SetColorItemNomal	(int nA, COLORREF clrColor);
	void SetColorItemNomal	(int nA1, COLORREF clrColor1, int nA2, COLORREF clrColor2);

	//----- Set Offset -----//
	void SetOffsetText	(int nX, int nY) { m_nOffsetTextX = nX; m_nOffsetTextY = nY; Invalidate(); }

	//----- Set Text Alignment -----//
	void SetAlignTextLT() { m_nTextAlign1 = 0; m_nTextAlign2 = 0; Invalidate(); }
	void SetAlignTextCT() { m_nTextAlign1 = 1; m_nTextAlign2 = 0; Invalidate(); }				   
	void SetAlignTextRT() { m_nTextAlign1 = 2; m_nTextAlign2 = 0; Invalidate(); }
	void SetAlignTextLM() { m_nTextAlign1 = 0; m_nTextAlign2 = 1; Invalidate(); }
	void SetAlignTextCM() { m_nTextAlign1 = 1; m_nTextAlign2 = 1; Invalidate(); }
	void SetAlignTextRM() { m_nTextAlign1 = 2; m_nTextAlign2 = 1; Invalidate(); }
	void SetAlignTextLB() { m_nTextAlign1 = 0; m_nTextAlign2 = 2; Invalidate(); }
	void SetAlignTextCB() { m_nTextAlign1 = 1; m_nTextAlign2 = 2; Invalidate(); }
	void SetAlignTextRB() { m_nTextAlign1 = 2; m_nTextAlign2 = 2; Invalidate(); }

	//-------------------- Scrollbar Control --------------------//
	void SetSBColorChannel(int nA, int nR, int nG, int nB) { m_pwndSBV->SetColorChannel(nA,nR,nG,nB); }
	void SetSBColorThumb(int nNomA, int nNomR, int nNomG, int nNomB, int nHiA, int nHiR, int nHiG, int nHiB) { 
		m_pwndSBV->SetColorThumb(nNomA, nNomR, nNomG, nNomB, nHiA, nHiR, nHiG, nHiB); }
	void SetSBColorArrow(int nNomA, int nNomR, int nNomG, int nNomB, int nHiA, int nHiR, int nHiG, int nHiB) { 
		m_pwndSBV->SetColorArrow(nNomA, nNomR, nNomG, nNomB, nHiA, nHiR, nHiG, nHiB); }
	void SetSBColorArrowBox(int nNomA, int nNomR, int nNomG, int nNomB, int nHiA, int nHiR, int nHiG, int nHiB) { 
		m_pwndSBV->SetColorArrowBox(nNomA, nNomR, nNomG, nNomB, nHiA, nHiR, nHiG, nHiB); }

private :
	void DrawBorder(Graphics *pG, CRect rcRect);
	void DrawItem(Graphics *pG, CRect rcItem, Color clrItem);
	void DrawText(Graphics *pG, CRect rcItem, CString strText, Color clrText);

	CScrollBarEx* m_pwndSBV;
	CRect	m_rcSBV;
	bool	m_bModeOneColor;
	int		m_nOffsetTextX;
	int		m_nOffsetTextY;
	int		m_nTextAlign1;
	int		m_nTextAlign2;
	int		m_nItemHeight;
	float	m_fSizeText;
	float	m_fSizeBorder;
	Color	m_clrBkg;
	Color	m_clrBorder;
	Color	m_clrItemNom1;
	Color	m_clrItemNom2;
	Color	m_clrItemHot;
	Color	m_clrTextNom;
	Color	m_clrTextHot;

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
};