#include "pch.h"
#include "FileLoader.h"

CFileLoader::CFileLoader(CWindow &TreeView) 
    : m_TreeView(TreeView) 
{
    m_tvis.hParent = TVI_ROOT ; 
    m_tvis.hInsertAfter = TVI_ROOT ; 
    m_tvis.item.mask = TVIF_TEXT ; 
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

void CFileLoader::Load(HWND hWnd, CPath &CurrentPath, HTREEITEM hTreeItem)
{
    WIN32_FIND_DATA FindFileData ; 
    CPath OriPath = CurrentPath ; 
    CurrentPath.Append(_T("*.*")) ; 
    // Current Path : C:\\*.* 
    // Origin Path : C:\\ 
    HANDLE hFind = FindFirstFile(CurrentPath, &FindFileData) ;  
    if(hFind == INVALID_HANDLE_VALUE)
    {
        return ;
    }
    while(true)
    {
        CString strFileName = FindFileData.cFileName ; 
        if((strFileName != _T(".")) && (strFileName != _T("..")))
        {
            CPath Path { strFileName } ;
            Path.Combine(OriPath, strFileName) ;
            CString strExt = Path.GetExtension() ; 
            if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY || IsImageFile(strExt))
            {
                m_tvis.hParent = hTreeItem ; 
                m_tvis.item.pszText = FindFileData.cFileName ; 
                HTREEITEM PrevTreeItem = TreeView_InsertItem(m_TreeView, &m_tvis) ; 
                Load(hWnd, Path, PrevTreeItem) ; // recursion call
            }
        }
        if(!FindNextFile(hFind, &FindFileData))
        {
            break ;
        }
    } 
    return ; 
}