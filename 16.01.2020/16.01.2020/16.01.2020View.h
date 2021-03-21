
#pragma once
#include "GLRenderer.h"

class CMy16012020View : public CView
{
protected: // create from serialization only
	CMy16012020View() noexcept;
	DECLARE_DYNCREATE(CMy16012020View)

public:
	CMy16012020Doc* GetDocument() const;
	CGLRenderer m_glRenderer;
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMy16012020View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnInitialUpdate();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in 16.01.2020View.cpp
inline CMy16012020Doc* CMy16012020View::GetDocument() const
   { return reinterpret_cast<CMy16012020Doc*>(m_pDocument); }
#endif

