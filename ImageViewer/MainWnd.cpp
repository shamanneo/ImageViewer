#include "pch.h"
#include "FileLoader.h"
#include "MainWnd.h"

CMainWnd::CMainWnd()
{

}

CMainWnd::~CMainWnd()
{

}

LRESULT CMainWnd::OnCommand(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL &/*bHandled*/) 
{
    return 0 ; 
}

LRESULT CMainWnd::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL &/*bHandled*/) 
{
    RECT rc ; 
    GetClientRect(&rc) ; 
    rc.right = rc.left + 200 ; 

    CreateTreeView(rc) ;
    CFileLoader FileLoader { m_TreeView } ; 
    CPath InitPath { _T("C:\\users") } ;
    FileLoader.Load(m_TreeView.m_hWnd, InitPath, TVI_ROOT) ; 

    const DWORD LV_STYLE = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | LVS_REPORT ;
    LVCOLUMN LvCol ;
    rc.left = rc.right + 10 ;
    rc.right = rc.left + 400 ;
    m_ListView.Create(WC_LISTVIEW, m_hWnd, rc, NULL, LV_STYLE, WS_EX_CLIENTEDGE) ;

    LvCol.mask = LVCF_TEXT | LVCF_WIDTH ;

    LvCol.pszText = const_cast<TCHAR *>(_T("이름")) ;
    LvCol.cx = 150 ;
    ListView_InsertColumn(m_ListView.m_hWnd, 0, &LvCol) ;

    LvCol.pszText = const_cast<TCHAR *>(_T("수정한 날짜")) ; 
    LvCol.cx = 120 ; 
    ListView_InsertColumn(m_ListView.m_hWnd, 1, &LvCol) ; 

    LvCol.pszText = const_cast<TCHAR *>(_T("유형")) ; 
    LvCol.cx = 76 ; 
    ListView_InsertColumn(m_ListView.m_hWnd, 2, &LvCol) ; 

    LvCol.pszText = const_cast<TCHAR *>(_T("크기")) ; 
    LvCol.cx = 50 ; 
    ListView_InsertColumn(m_ListView.m_hWnd, 3, &LvCol) ; 
    return 0 ; 
}

LRESULT CMainWnd::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL &/*bHandled*/) 
{
    PAINTSTRUCT ps ; 
    HDC hDC = BeginPaint(&ps) ; 
    UNREFERENCED_PARAMETER(hDC) ; 
    EndPaint(&ps) ; 
    return 0 ; 
}

LRESULT CMainWnd::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL &/*bHandled*/) 
{
    RECT rc ; 
    GetClientRect(&rc) ; 
    rc.right = rc.left + 200 ; 
    ::SetWindowPos(m_TreeView, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW) ; 
    rc.left = rc.right + 10 ;
    rc.right = rc.left + 400 ;
    ::SetWindowPos(m_ListView, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW) ; 
    return 0 ; 
}

LRESULT CMainWnd::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL &/*bHandled*/)
{
    PostQuitMessage(0) ; 
    return 0 ; 
}

void CMainWnd::CreateTreeView(RECT &rc) 
{
    const DWORD dwTVStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT ;
    m_TreeView.Create(WC_TREEVIEW, m_hWnd, rc, NULL, dwTVStyle, WS_EX_CLIENTEDGE) ;

    /*
    HTREEITEM hTreeItem ; 
    TVINSERTSTRUCT tvis ; 
    tvis.hParent = TVI_ROOT ; 
    tvis.hInsertAfter = TVI_ROOT ; 
    tvis.item.mask = TVIF_TEXT ;
    tvis.item.pszText = const_cast<TCHAR *>(_T("사진")) ;
    hTreeItem = TreeView_InsertItem(m_TreeView.m_hWnd, &tvis) ; 
    tvis.hParent = hTreeItem ; 
    tvis.item.pszText = const_cast<TCHAR *>(_T("Saved Pictures")) ;
    hTreeItem = TreeView_InsertItem(m_TreeView.m_hWnd, &tvis) ; 
    */
}

void CMainWnd::CreateListView(RECT &rc) 
{
    const DWORD dwLVStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | LVS_REPORT ;
    m_ListView.Create(WC_LISTVIEW, m_hWnd, rc, NULL, dwLVStyle, WS_EX_CLIENTEDGE) ; 
}