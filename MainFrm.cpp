
// MainFrm.cpp : CMainFrame 
//

#include "stdafx.h"
#include "Draw.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

const int  iMaxUserToolbars = 10;
const UINT uiFirstUserToolBarId = AFX_IDW_CONTROLBAR_FIRST + 40;
const UINT uiLastUserToolBarId = uiFirstUserToolBarId + iMaxUserToolbars - 1;

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_COMMAND(ID_BUTTON32772,&CMainFrame::DrawQuit)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 

CMainFrame::CMainFrame()
{
	//===============================================================
	
	//1.CreateCompatibleDC   2.SelectObject   3.BitBlt
	//===============================================================
	CWindowDC dc_DeskTop(GetDesktopWindow());

	CBitmap* bitmap=new CBitmap;
	bitmap->CreateCompatibleBitmap(&dc_DeskTop,1920,1080);
	//===============================================================

	CDC cdc;
	cdc.CreateCompatibleDC(&dc_DeskTop);
	cdc.SelectObject(bitmap);
	//===============================================================
	cdc.BitBlt(0,0,1920,1080,&dc_DeskTop,0,0,SRCCOPY);

	sk_bmpDesktop.push(bitmap);
}

CMainFrame::~CMainFrame()
{
	while (sk_bmpDesktop.empty()== false)
	{
		delete sk_bmpDesktop.top();
		sk_bmpDesktop.pop();
	}
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR1))
	{
		TRACE0("ToolBar Failed\n");
		return -1;      
	}

	this->SetMenu(NULL);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style=WS_POPUP;
	return TRUE;
}

// CMainFrame 

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 

void CMainFrame::DrawQuit(){
	this->PostMessage(WM_CLOSE);
}
