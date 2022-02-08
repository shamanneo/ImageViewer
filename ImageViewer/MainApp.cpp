#include "pch.h"
#include "Resource.h"
#include "MainApp.h"

static CMainApp *g_pMainApp = nullptr ; 

CMainApp::CMainApp()
{
    RECT rc ; 
    GetClientRect(m_MainWnd, &rc) ; 
    rc.right = rc.left + 200 ; 
    const DWORD dwTVStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT ;
    m_TreeView.Create(WC_TREEVIEW, m_MainWnd, rc, NULL, dwTVStyle, WS_EX_CLIENTEDGE, IDC_MAIN_TREE_VIEW) ;

    rc.left = rc.right + 10 ;
    rc.right = rc.left + 400 ;
    const DWORD dwLVStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | LVS_REPORT ;
    m_ListView.Create(WC_LISTVIEW, m_MainWnd, rc, NULL, dwLVStyle, WS_EX_CLIENTEDGE, IDC_MAIN_LIST_VIEW) ;
}

CMainApp::~CMainApp()
{

}

int CMainApp::Run(HINSTANCE hInstance, int nCmdShow)
{
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_IMAGEVIEWER)) ;
    MSG msg ;

    m_MainWnd.Create(NULL, NULL, _T("Viewer"), WS_OVERLAPPEDWINDOW, 0) ; 
    m_MainWnd.ShowWindow(nCmdShow) ; 
    m_MainWnd.UpdateWindow() ; 

    while (::GetMessage(&msg, nullptr, 0, 0)) // main message loop.
    {
        if (!::TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            ::TranslateMessage(&msg) ;
            ::DispatchMessage(&msg) ;
        }
    }
    return (int) msg.wParam ; 
}

//      static 

CMainApp &CMainApp::GetInstance() 
{
    if(g_pMainApp == nullptr)
    {
        g_pMainApp = new CMainApp ; 
    }
    return *g_pMainApp ; 
}

void CMainApp::Release()
{
    if(g_pMainApp != nullptr)
    {
        delete g_pMainApp ; 
        g_pMainApp = nullptr ; 
    }
}