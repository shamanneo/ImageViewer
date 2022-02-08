#include "pch.h"
#include "ItemAttributes.h"
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

void CFileLoader::LoadFiles(CWindow &TreeViewWnd, CWindow &ListViewWnd, CPath &Path, HTREEITEM hParentItem) 
{
    WIN32_FIND_DATA FindFileData ; 
    CPath TempPath = Path ; 
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
                InsertTreeView(TreeViewWnd, Path, FindFileData, hParentItem) ; 
                InsertListView(ListViewWnd, Path, FindFileData, hParentItem) ; 
            }
        }
        if(!FindNextFile(hFind, &FindFileData))
        {
            break ;
        }
    }
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
}

void CFileLoader::InsertListView(CWindow &ListViewWnd, CPath &Path, WIN32_FIND_DATA &FindFileData, HTREEITEM &hParentItem) 
{
    return ; 
}