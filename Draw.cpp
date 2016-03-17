
// Draw.cpp : 

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Draw.h"
#include "MainFrm.h"

#include "DrawDoc.h"
#include "DrawView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDrawApp

BEGIN_MESSAGE_MAP(CDrawApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CDrawApp::OnAppAbout)

	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)

	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CDrawApp 
CDrawApp::CDrawApp()
{

	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED

	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	SetAppID(_T("Draw.AppID.NoVersion"));

	
}



CDrawApp theApp;


// CDrawApp Init

BOOL CDrawApp::InitInstance()
{
	
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	//  OLE Init
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	
	SetRegistryKey(_T("Local Process"));
	LoadStdProfileSettings(4);  



	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDrawDoc),
		RUNTIME_CLASS(CMainFrame),       
		RUNTIME_CLASS(CDrawView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);



	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);




	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	//Update Window
	m_pMainWnd->ShowWindow(SW_MAXIMIZE);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

int CDrawApp::ExitInstance()
{
	
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}






class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();


	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 


protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


void CDrawApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CDrawApp 



