
// DrawView.cpp : CDrawView 
//

#include "stdafx.h"

#ifndef SHARED_HANDLERS
#include "Draw.h"
#endif

#include "DrawDoc.h"
#include "DrawView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
enum {CURVE,LINE,ELLIPES,RECTANGLE,ANGLE,FILL};



IMPLEMENT_DYNCREATE(CDrawView, CView)

BEGIN_MESSAGE_MAP(CDrawView, CView)

	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_BUTTON32778,&CDrawView::OnColorDialog)
	ON_COMMAND(ID_BUTTON32779,&CDrawView::OnFill)
	ON_COMMAND(ID_BUTTON32780,&CDrawView::OnSave)
	ON_COMMAND_RANGE(ID_BUTTON32773,ID_BUTTON32777,&CDrawView::OnUpdateStyle)
	ON_COMMAND(ID_ACCELERATOR_Z, &CDrawView::OnAcceleratorZ)
END_MESSAGE_MAP()

// CDrawView
CDrawView::CDrawView()
{
	m_nMouseDownFlag=FALSE;
	m_style=0;
	color=RGB(100,255,100);

}

CDrawView::~CDrawView()
{
}

BOOL CDrawView::PreCreateWindow(CREATESTRUCT& cs)
{
	

	return CView::PreCreateWindow(cs);
}

// CDrawView 

void CDrawView::OnDraw(CDC* /*pDC*/)
{
	CDrawDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	CMainFrame* frame=(CMainFrame*)AfxGetMainWnd();
	CClientDC m_DeskTopClientDc(this);

	CDC cdc;
	cdc.CreateCompatibleDC(&m_DeskTopClientDc);
	cdc.SelectObject(frame->sk_bmpDesktop.top());
	m_DeskTopClientDc.BitBlt(0,0,1920,1080,&cdc,0,0,SRCCOPY);
}


// CDrawView 

BOOL CDrawView::OnPreparePrinting(CPrintInfo* pInfo)
{

	return DoPreparePrinting(pInfo);
}

void CDrawView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}

void CDrawView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{

}


// CDrawView
#ifdef _DEBUG
void CDrawView::AssertValid() const
{
	CView::AssertValid();
}

void CDrawView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDrawDoc* CDrawView::GetDocument() const 
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawDoc)));
	return (CDrawDoc*)m_pDocument;
}
#endif //_DEBUG





void CDrawView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar==VK_ESCAPE)
	{
		CMainFrame* frame=(CMainFrame*)AfxGetMainWnd();
		frame->PostMessage(WM_CLOSE);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CDrawView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_nMouseDownFlag=TRUE;
	m_MouseDownPoint=point;

	if (m_style==FILL)
	{
		CClientDC dc(this);
		CBrush brush(color);
		dc.SelectObject(brush);
		dc.ExtFloodFill(point.x,point.y,dc.GetPixel(point),FLOODFILLSURFACE);

	}

	CView::OnLButtonDown(nFlags, point);
}


void CDrawView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_nMouseDownFlag=FALSE;
	CClientDC dc(this);
	CBitmap* bitmap=new CBitmap;
	bitmap->CreateCompatibleBitmap(&dc,1920,1080);
	CDC cdc;
	cdc.CreateCompatibleDC(&dc);
	cdc.SelectObject(bitmap);
	cdc.BitBlt(0,0,1920,1080,&dc,0,0,SRCCOPY);
	CMainFrame* frame=(CMainFrame*)AfxGetMainWnd();
	frame->sk_bmpDesktop.push(bitmap);

	CView::OnLButtonUp(nFlags, point);
}


void CDrawView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_nMouseDownFlag==TRUE)
	{
		if (m_style==CURVE)
		{
			CClientDC dc(this);
			dc.MoveTo(m_MouseDownPoint);
			dc.LineTo(point);
			m_MouseDownPoint=point;
			return;
		}
		CClientDC dc(this);

		CDC memdc;
		memdc.CreateCompatibleDC(&dc);
		CBitmap membitmap;
		membitmap.CreateCompatibleBitmap(&dc,1920,1080);
		memdc.SelectObject(&membitmap);

		CDC cdc;
		cdc.CreateCompatibleDC(&dc);
		CMainFrame* frame=(CMainFrame*)AfxGetMainWnd();
		cdc.SelectObject(frame->sk_bmpDesktop.top());

		memdc.BitBlt(0,0,1920,1080,&cdc,0,0,SRCCOPY);
		switch (m_style)
		{
		case LINE:
			{
				memdc.MoveTo(m_MouseDownPoint);
				memdc.LineTo(point);
			}
			break;
		case ELLIPES:
			{
				memdc.SelectStockObject(NULL_BRUSH);
				memdc.Ellipse(m_MouseDownPoint.x,m_MouseDownPoint.y,point.x,point.y);
			}
			break;
		case RECTANGLE:
			{
				CBrush brush(color);
				memdc.SelectObject(brush);
				memdc.Rectangle(m_MouseDownPoint.x,m_MouseDownPoint.y,point.x,point.y);
			}
			break;
		case ANGLE:
			{
				POINT arr[]={
					{(point.x-m_MouseDownPoint.x)/2+m_MouseDownPoint.x,m_MouseDownPoint.y},
					{point.x,point.y},
					{m_MouseDownPoint.x,point.y}
				};
				memdc.SelectStockObject(NULL_BRUSH);
				memdc.Polygon(arr,3);
			}
			break;
		}
		dc.BitBlt(0,0,1920,1080,&memdc,0,0,SRCCOPY);
	}

	CView::OnMouseMove(nFlags, point);
}
void CDrawView::OnUpdateStyle(UINT uID){
	m_style=uID-ID_BUTTON32773;
}
void CDrawView::OnColorDialog(){
	CColorDialog colorDlg;
	if (colorDlg.DoModal()==IDOK)
	{
		color=colorDlg.GetColor();
	}
	
}
void CDrawView::OnFill(){
	m_style=FILL;
}
void CDrawView::OnSave(){
	CFileDialog dlg(FALSE,L"jpg",L"无标题");
	if (dlg.DoModal()==IDOK)
	{
		CString str;
		str=dlg.GetPathName();

		CMainFrame* frame=(CMainFrame*)AfxGetMainWnd();
		CImage img;
		HBITMAP bitmap=(HBITMAP)(frame->sk_bmpDesktop.top()->m_hObject);
		img.Attach(bitmap);
		img.Save(str);
	}


}

void CDrawView::OnAcceleratorZ()
{
	CMainFrame* frame=(CMainFrame*)AfxGetMainWnd();
	if (frame->sk_bmpDesktop.size()>1)
	{
		delete frame->sk_bmpDesktop.top();
		frame->sk_bmpDesktop.pop();

		CClientDC m_DeskTopClientDc(this);

		CDC cdc;
		cdc.CreateCompatibleDC(&m_DeskTopClientDc);
		cdc.SelectObject(frame->sk_bmpDesktop.top());
		m_DeskTopClientDc.BitBlt(0,0,1920,1080,&cdc,0,0,SRCCOPY);
	}
}
