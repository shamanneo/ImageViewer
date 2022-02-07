#include "pch.h"
#include "ItemAttributes.h"
#include "FileLoader.h"

CFileLoader::CFileLoader(CWindow &TreeView) 
    : m_TreeView(TreeView) 
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

void CFileLoader::LoadFiles(CPath &Path, HTREEITEM hParentItem) 
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
        ItemAttributes *pItemAttributes = new ItemAttributes ; 
        CPath CurrentFileName { Path } ;
        if(((StrCmpCW(FindFileData.cFileName, L".") != 0) && ((StrCmpCW(FindFileData.cFileName, L"..") != 0))))
        {
            if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY || IsImageFile(FindFileData.cFileName))
            {
                CurrentFileName.Append(FindFileData.cFileName) ; 
                pItemAttributes->m_MyPath = CurrentFileName ; 
                m_tvis.hParent = hParentItem ; 
                m_tvis.item.pszText = FindFileData.cFileName ; 
                m_tvis.item.lParam = reinterpret_cast<LPARAM>(pItemAttributes) ; 
                TreeView_InsertItem(m_TreeView, &m_tvis) ; 
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