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

bool CFileLoader::IsImageFile(CString &str) 
{
    if((str.CompareNoCase(_T(".png")) == 0) || (str.CompareNoCase(_T(".jpg")) == 0))
    {
        return true ;
    }
    return false ; 
}

void CFileLoader::LoadFiles(CWindow &TreeViewWnd, CWindow &ListViewWnd, ItemAttributes *pItemAttributes, HTREEITEM hParentItem) 
{
    ListView_DeleteAllItems(ListViewWnd) ; 
    WIN32_FIND_DATA FindFileData ;
    CPath path = pItemAttributes->m_MyPath ; 
    path.Append(_T("*.*")) ; 
    HANDLE hFind = FindFirstFile(path, &FindFileData) ;  
    if(hFind == INVALID_HANDLE_VALUE)
    {
        return ;
    }
    while(true)
    {
        if(((StrCmpCW(FindFileData.cFileName, L".") != 0) && ((StrCmpCW(FindFileData.cFileName, L"..") != 0))))
        {
            CPath TempPath = FindFileData.cFileName ; 
            CString strExtension = TempPath.GetExtension() ; 
            if((pItemAttributes->m_bExpanded == false) && ((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY))
            {
                InsertTreeView(TreeViewWnd, pItemAttributes->m_MyPath, FindFileData, hParentItem) ; 
            }
            if(IsImageFile(strExtension))
            {
                InsertListView(ListViewWnd, pItemAttributes->m_MyPath, FindFileData) ; 
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

void CFileLoader::InsertListView(CWindow &ListViewWnd, CPath &Path, WIN32_FIND_DATA &FindFileData) 
{
    ItemAttributes *pItemAttributes = new ItemAttributes ; 
    pItemAttributes->m_MyPath = Path ;
    CopyMemory(&pItemAttributes->m_FindFileData, &FindFileData, sizeof(FindFileData)) ; 
    LVITEM lvI ; 
    lvI.pszText = FindFileData.cFileName ; 
    lvI.mask = LVIF_TEXT | LVIF_PARAM ; 
    lvI.stateMask = 0 ; 
    lvI.iSubItem = 0 ; 
    lvI.state = 0 ; 
    lvI.iItem = 0 ; 
    lvI.iImage = 0 ; 
    lvI.lParam = reinterpret_cast<LPARAM>(pItemAttributes) ; 
    INT n = ListView_InsertItem(ListViewWnd, &lvI) ; 
    if(n == -1)
    {
        return ;
    }
    FILETIME FileTime ;
    CopyMemory(&FileTime, &FindFileData.ftLastWriteTime, sizeof(FileTime)) ; 
    CTime time { FileTime } ; 
    CString str = time.Format(_T("%Y-%m-%d %H:%M")) ; 
    ListView_SetItemText(ListViewWnd, n, 1, str.GetBuffer()) ; 
}

