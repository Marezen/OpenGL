#pragma region fiksno
#include "pch.h"
#include "framework.h"
#ifndef SHARED_HANDLERS
#include "16.01.2020.h"
#endif
#include "16.01.2020Doc.h"
#include "16.01.2020View.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CMy16012020View, CView)

BEGIN_MESSAGE_MAP(CMy16012020View, CView)
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

CMy16012020View::CMy16012020View() noexcept
{
}
CMy16012020View::~CMy16012020View()
{
}
BOOL CMy16012020View::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}
#pragma endregion

void CMy16012020View::OnDraw(CDC* pDC)
{
	CMy16012020Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_glRenderer.DrawScene(pDC);
}
#pragma region .....
BOOL CMy16012020View::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}
void CMy16012020View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
void CMy16012020View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}
#ifdef _DEBUG
void CMy16012020View::AssertValid() const
{
	CView::AssertValid();
}
void CMy16012020View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
CMy16012020Doc* CMy16012020View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy16012020Doc)));
	return (CMy16012020Doc*)m_pDocument;
}
#endif //_DEBUG
#pragma endregion
#pragma region handlers
int CMy16012020View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}
void CMy16012020View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}
void CMy16012020View::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}
BOOL CMy16012020View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
void CMy16012020View::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}
void CMy16012020View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RIGHT) m_glRenderer.ugaox += 0.1;
	if (nChar == VK_LEFT) m_glRenderer.ugaox -= 0.1;
	if (nChar == VK_UP) m_glRenderer.ugaoy += 0.1;
	if (nChar == VK_DOWN) m_glRenderer.ugaoy -= 0.1;

	if (nChar == VK_ADD)
	{
		if (m_glRenderer.r < 50)
			m_glRenderer.r += 1;
	}
	if (nChar == VK_SUBTRACT)
	{
		if (m_glRenderer.r > 8)
			m_glRenderer.r -= 1;
	}

	m_glRenderer.xeye = sin(m_glRenderer.ugaoy) * sin(m_glRenderer.ugaox) * m_glRenderer.r;
	m_glRenderer.yeye = cos(m_glRenderer.ugaoy) * m_glRenderer.r;
	m_glRenderer.zeye = sin(m_glRenderer.ugaoy) * cos(m_glRenderer.ugaox) * m_glRenderer.r;

	if (nChar == '1') m_glRenderer.angle1 += 5;
	if (nChar == '2') m_glRenderer.angle1 -= 5;
	if (nChar == '3') m_glRenderer.angle2 += 5;
	if (nChar == '4') m_glRenderer.angle2 -= 5;
	if (nChar == '5') m_glRenderer.angle3 += 5;
	if (nChar == '6') m_glRenderer.angle3 -= 5;
	if (nChar == '7') m_glRenderer.angle4 += 5;
	if (nChar == '8') m_glRenderer.angle4 -= 5;

	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
#pragma endregion