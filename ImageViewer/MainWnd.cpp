#include "pch.h"
#include "FileLoader.h"
#include "ItemAttributes.h"
#include "resource.h"
#include "MainApp.h"
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
    LONG end = rc.right ; 
    rc.right = rc.left + 200 ; 
    CreateTreeView(rc) ;
    rc.left = rc.right + 10 ;
    rc.right = rc.left + 300 ;
    CreateListView(rc) ; 
    rc.left = rc.right + 10 ;
    rc.right = end - 10 ; 
    m_ImageWnd.Create(m_hWnd, rc, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, WS_EX_CLIENTEDGE) ; 
    CFileLoader FileLoader ;
    ItemAttributes InitItemAttributes ;
    CPath InitPath { _T("C:\\users") } ;
    InitItemAttributes.m_MyPath = InitPath ; 
    FileLoader.LoadFiles(m_TreeView, m_ListView, &InitItemAttributes, TVI_ROOT) ; 
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
    LONG end = rc.right ; 
    rc.right = rc.left + 200 ; 
    ::SetWindowPos(m_TreeView, NULL, 0, 0, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW) ; 
    rc.left = rc.right + 10 ;
    rc.right = rc.left + 300 ;
    ::SetWindowPos(m_ListView, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW) ; 
    rc.left = rc.right + 10 ;
    rc.right = end - 10 ; 
    ::SetWindowPos(m_ImageWnd, NULL, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW) ; 
    return 0 ; 
}

LRESULT CMainWnd::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL &/*bHandled*/)
{
    PostQuitMessage(0) ; 
    return 0 ; 
}

LRESULT CMainWnd::OnSelectedChanged(int /*idCtrl*/, LPNMHDR pNHDR, BOOL &/*bHandled*/)
{
    TCHAR szBuffer[30] ; 
    CFileLoader FileLoader ;
    NMTREEVIEW *pNMTV = reinterpret_cast<NMTREEVIEW *>(pNHDR) ; 
    TVITEM Item ;
    Item.mask = TVIF_TEXT | TVIF_PARAM ; 
    Item.hItem = pNMTV->itemNew.hItem ; 
    Item.pszText = szBuffer ; 
    Item.cchTextMax = _countof(szBuffer) ; 
    TreeView_GetItem(m_TreeView, &Item) ; 
    ItemAttributes *pItemAttributes = reinterpret_cast<ItemAttributes *>(Item.lParam) ; 
    FileLoader.LoadFiles(m_TreeView, m_ListView, pItemAttributes, Item.hItem) ; 
    return 0 ; 
}

LRESULT CMainWnd::OnDeleteTItem(int /*idCtrl*/, LPNMHDR pNHDR, BOOL &/*bHandled*/)
{
    NMTREEVIEW *pNMTV = reinterpret_cast<NMTREEVIEW *>(pNHDR) ; 
    ItemAttributes *pItemAttributes = reinterpret_cast<ItemAttributes *>(pNMTV->itemOld.lParam) ; 
    delete pItemAttributes ; 
    return 0 ; 
}

LRESULT CMainWnd::OnItemChanged(int /*idCtrl*/, LPNMHDR pNHDR, BOOL &/*bHandled*/)
{
    NMLISTVIEW *pNMLV = reinterpret_cast<NMLISTVIEW *>(pNHDR) ; 
    if(pNMLV->uOldState == 0)
    {
        LVITEM Item ; 
        Item.mask = LVIF_PARAM ; 
        Item.iSubItem = 0 ; 
        Item.state = 0 ; 
        Item.iItem = pNMLV->iItem ; 
        ListView_GetItem(m_ListView, &Item) ; 
        ItemAttributes *pItemAttributes = reinterpret_cast<ItemAttributes *>(Item.lParam) ; 
        CPath path ;
        path.Combine(pItemAttributes->m_MyPath, pItemAttributes->m_FindFileData.cFileName) ; 
        Draw(path) ; 
    }
    return 0 ; 
}

LRESULT CMainWnd::OnDeleteLItem(int /*idCtrl*/, LPNMHDR pNHDR, BOOL &/*bHandled*/)
{
    NMLISTVIEW *pNMLV = reinterpret_cast<NMLISTVIEW *>(pNHDR) ; 
    ItemAttributes *pItemAttributes = reinterpret_cast<ItemAttributes *>(pNMLV->lParam) ; 
    delete pItemAttributes ; 
    return 0 ; 
}

void CMainWnd::CreateTreeView(RECT &rc) 
{
    const DWORD dwTVStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT ;
    m_TreeView.Create(WC_TREEVIEW, m_hWnd, rc, NULL, dwTVStyle, WS_EX_CLIENTEDGE, IDC_MAIN_TREE_VIEW) ;
    return ; 
}

void CMainWnd::CreateListView(RECT &rc) 
{
    const DWORD dwLVStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | LVS_REPORT ;
    m_ListView.Create(WC_LISTVIEW, m_hWnd, rc, NULL, dwLVStyle, WS_EX_CLIENTEDGE, IDC_MAIN_LIST_VIEW) ;
    LVCOLUMN LvCol ;
    LvCol.mask = LVCF_TEXT | LVCF_WIDTH ;

    LvCol.pszText = const_cast<TCHAR *>(_T("????")) ;
    LvCol.cx = 150 ;
    ListView_InsertColumn(m_ListView.m_hWnd, 0, &LvCol) ;

    LvCol.pszText = const_cast<TCHAR *>(_T("?????? ????")) ; 
    LvCol.cx = 146 ; 
    ListView_InsertColumn(m_ListView.m_hWnd, 1, &LvCol) ; 
    return ; 
}

void CMainWnd::Draw(CPath &Path) 
{
    CMainApp::GetInstance().SetFileName(Path) ; 
    ::InvalidateRect(m_ImageWnd, nullptr, true) ;
    ::UpdateWindow(m_ImageWnd) ; 
    return ;
}
