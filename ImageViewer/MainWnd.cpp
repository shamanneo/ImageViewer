#include "pch.h"
#include "FileLoader.h"
#include "ItemAttributes.h"
#include "resource.h"
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
    FileLoader.LoadFiles(InitPath) ; 
    LVCOLUMN LvCol ;
    rc.left = rc.right + 10 ;
    rc.right = rc.left + 400 ;
    CreateListView(rc) ; 
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

    LVITEM lvItem ;
    lvItem.mask = LVIF_TEXT ;
    lvItem.pszText = LPSTR_TEXTCALLBACK ; 
    ListView_InsertItem(m_ListView, &lvItem) ;
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

LRESULT CMainWnd::OnSelectedChanged(int /*idCtrl*/, LPNMHDR pNHDR, BOOL &/*bHandled*/)
{
    TCHAR szBuffer[30] ; 
    NMTREEVIEW *pNMTV = reinterpret_cast<NMTREEVIEW *>(pNHDR) ; 
    TVITEM Item ;
    Item.mask = TVIF_TEXT | TVIF_PARAM ; 
    Item.hItem = pNMTV->itemNew.hItem ; 
    Item.pszText = szBuffer ; 
    Item.cchTextMax = _countof(szBuffer) ; 
    TreeView_GetItem(m_TreeView, &Item) ; 
    ItemAttributes *pItemAttributes = reinterpret_cast<ItemAttributes *>(Item.lParam) ; 
    if(!pItemAttributes->m_bExpanded)
    {
        pItemAttributes->m_bExpanded = true ; 
        CFileLoader FileLoader { m_TreeView } ; 
        FileLoader.LoadFiles(pItemAttributes->m_MyPath, Item.hItem) ; 
    }
    INT nCount = ListView_GetItemCount(m_ListView) ; 
    while(nCount--) 
    {
        ListView_DeleteItem(m_ListView, 0) ; 
    }
    return 0 ; 
}

LRESULT CMainWnd::OnDeleteItem(int /*idCtrl*/, LPNMHDR pNHDR, BOOL &/*bHandled*/)
{
    NMTREEVIEW *pNMTV = reinterpret_cast<NMTREEVIEW *>(pNHDR) ; 
    ItemAttributes *pItemAttributes = reinterpret_cast<ItemAttributes *>(pNMTV->itemOld.lParam) ; 
    delete pItemAttributes ; 
    return 0 ; 
}

LRESULT CMainWnd::OnGetDispInfo(int /*idCtrl*/, LPNMHDR pNHDR, BOOL &/*bHandled*/) 
{
    NMLVDISPINFO *plvdi = reinterpret_cast<NMLVDISPINFO *>(pNHDR) ; 
    switch(plvdi->item.iSubItem)
    {
        case 0 :
        {
            plvdi->item.pszText = const_cast<TCHAR *>(_T("HELLO")) ; 
            break ; 
        }
        case 1 :
        {
            plvdi->item.pszText = const_cast<TCHAR *>(_T("WORLD")) ; 
            break ; 
        }
        case 2 :
        {
            plvdi->item.pszText = const_cast<TCHAR *>(_T("HELLO")) ; 
            break ; 
        }
        case 3 :
        {
            plvdi->item.pszText = const_cast<TCHAR *>(_T("HELLO")) ; 
            break ; 
        }
        default :
        {
            ATLASSERT(0) ; 
            break ; 
        }
    }
    return 0 ; 
}

void CMainWnd::CreateTreeView(RECT &rc) 
{
    const DWORD dwTVStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT ;
    m_TreeView.Create(WC_TREEVIEW, m_hWnd, rc, NULL, dwTVStyle, WS_EX_CLIENTEDGE, IDC_MAIN_TREE_VIEW) ;
}

void CMainWnd::CreateListView(RECT &rc) 
{
    const DWORD dwLVStyle = WS_CHILD | WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | LVS_REPORT ;
    m_ListView.Create(WC_LISTVIEW, m_hWnd, rc, NULL, dwLVStyle, WS_EX_CLIENTEDGE, IDC_MAIN_LIST_VIEW) ;

    LVITEM lvI ; 
    lvI.pszText = LPSTR_TEXTCALLBACK ; 
    lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE ; 
    lvI.stateMask = 0 ; 
    lvI.iSubItem = 0 ; 
    lvI.state = 0 ; 

    for(INT nIndex = 0 ; nIndex < 10 ; nIndex++)
    {
        lvI.iItem = nIndex ; 
        lvI.iImage = nIndex ; 
        if(ListView_InsertItem(m_ListView, &lvI) == -1)
        {
            return ;
        }
    }
}
