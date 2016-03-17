

#pragma once


class CDrawView : public CView
{
protected: 
	CDrawView();
	DECLARE_DYNCREATE(CDrawView)


public:
	CDrawDoc* GetDocument() const;

public:
	BOOL m_nMouseDownFlag;
	CPoint m_MouseDownPoint;
	int m_style;
	COLORREF color;

public:
	virtual void OnDraw(CDC* pDC);  // rewrite
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

public:
	virtual ~CDrawView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnUpdateStyle(UINT uID);
	afx_msg void OnColorDialog();
	afx_msg void OnFill();
	afx_msg void OnSave();
	afx_msg void OnAcceleratorZ();
};

#ifndef _DEBUG  // DrawView.cpp 
inline CDrawDoc* CDrawView::GetDocument() const
   { return reinterpret_cast<CDrawDoc*>(m_pDocument); }
#endif

