#include "pch.h"
#include "FileLoader.h"

CFileLoader::CFileLoader() 
{
    m_tvis.hParent = TVI_ROOT ; 
    m_tvis.hInsertAfter = TVI_ROOT ; 
    m_tvis.item.mask = TVIF_TEXT | TVIF_PARAM ; 
}

CFileLoader::~CFileLoader() 
{

}

bool CFileLoader::IsImageFile(CString str) 
{
    if((str.CompareNoCase(_T(".png"))) || (str.CompareNoCase(_T(".jpg"))))
    {
        return true ;
    }
    return false ; 
}

void CFileLoader::LoadFiles(CWindow &TreeViewWnd, CWindow &ListViewWnd, ItemAttributes *pItemAttributes, HTREEITEM hParentItem) 
{
    ListView_DeleteAllItems(ListViewWnd) ; 
    WIN32_FIND_DATA FindFileData ;
    CPath TempPath = pItemAttributes->m_MyPath ; 
    TempPath.Append(_T("*.*")) ; 
    HANDLE hFind = FindFirstFile(TempPath, &FindFileData) ;  
    if(hFind == INVALID_HANDLE_VALUE)
    {
        return ;
    }
    while(true)
    {
        if(((StrCmpCW(FindFileData.cFileName, L".") != 0) && ((StrCmpCW(FindFileData.cFileName, L"..") != 0))))
        {
            if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY || IsImageFile(FindFileData.cFileName))
            {
                if(pItemAttributes->m_bExpanded == false)
                {
                    InsertTreeView(TreeViewWnd, pItemAttributes->m_MyPath, FindFileData, hParentItem) ; 
                }
                InsertListView(ListViewWnd, FindFileData) ; 
            }
        }
        if(!FindNextFile(hFind, &FindFileData))
        {
            break ;
        }
    }
    pItemAttributes->m_bExpanded = true ; 
    FindClose(hFind) ; 
    return ; 
}

void CFileLoader::InsertTreeView(CWindow &TreeViewWnd, CPath &Path, WIN32_FIND_DATA &FindFileData, HTREEITEM &hParentItem) 
{
    CPath CurrentFileName { Path } ;
    ItemAttributes *pItemAttributes = new ItemAttributes ; 
    CurrentFileName.Append(FindFileData.cFileName) ; 
    pItemAttributes->m_MyPath = CurrentFileName ; 
    m_tvis.hParent = hParentItem ; 
    m_tvis.item.pszText = FindFileData.cFileName ; 
    m_tvis.item.lParam = reinterpret_cast<LPARAM>(pItemAttributes) ; 
    TreeView_InsertItem(TreeViewWnd, &m_tvis) ; 
    return ; 
}

void CFileLoader::InsertListView(CWindow &ListViewWnd, WIN32_FIND_DATA &FindFileData) 
{
    WIN32_FIND_DATA *pFindFileData = new WIN32_FIND_DATA ;
    CopyMemory(pFindFileData, &FindFileData, sizeof(FindFileData)) ; 
    LVITEM lvI ; 
    lvI.pszText = FindFileData.cFileName ; 
    lvI.mask = LVIF_TEXT | LVIF_PARAM ; 
    lvI.stateMask = 0 ; 
    lvI.iSubItem = 0 ; 
    lvI.state = 0 ; 
    lvI.iItem = 0 ; 
    lvI.iImage = 0 ; 
    lvI.lParam = reinterpret_cast<LPARAM>(pFindFileData) ; 
    INT n = ListView_InsertItem(ListViewWnd, &lvI) ; 
    if(n == -1)
    {
        return ;
    }
    FILETIME FileTime = pFindFileData->ftLastAccessTime ; 
    CTime time { FileTime } ; 
    CString str = time.Format(_T("%Y-%m-%d %H:%M")) ; 
    ListView_SetItemText(ListViewWnd, n, 1, str.GetBuffer()) ; 
    ListView_SetItemText(ListViewWnd, n, 2, const_cast<WCHAR *>(_T("TBD"))) ; 
    ListView_SetItemText(ListViewWnd, n, 3, const_cast<WCHAR *>(_T("TBD"))) ; 
}

