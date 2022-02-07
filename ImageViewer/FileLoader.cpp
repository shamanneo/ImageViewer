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

void CFileLoader::LoadFiles(CPath &Path) 
{
    WIN32_FIND_DATA FindFileData ; 
    CAutoPtr<ItemAttributes> spItemAttributes { new ItemAttributes } ; 
    spItemAttributes->m_MyPath = Path ; 
    Path.Append(_T("*.*")) ; 
    HANDLE hFind = FindFirstFile(Path, &FindFileData) ;  
    if(hFind == INVALID_HANDLE_VALUE)
    {
        return ;
    }
    while(true)
    {
        CString strCurrentFileName = FindFileData.cFileName ; 
        if((strCurrentFileName != _T(".")) && (strCurrentFileName != _T("..")))
        {
            CPath FileName { strCurrentFileName } ;
            if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY || IsImageFile(FileName.GetExtension()))
            {
                m_tvis.item.pszText = strCurrentFileName.GetBuffer() ; 
                m_tvis.item.lParam = (LPARAM)spItemAttributes.m_p ; 
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