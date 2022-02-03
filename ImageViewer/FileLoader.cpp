#include "pch.h"
#include "FileLoader.h"

CFileLoader::CFileLoader() 
{
    m_path = "C:\\*" ; 
}

CFileLoader::~CFileLoader() 
{

}

void CFileLoader::Load(HWND hWnd, CPath &CurrentPath)
{
    WIN32_FIND_DATA FindFileData ; 
    CPath OriPath = CurrentPath ; 
    CurrentPath.Append(_T("*.*")) ; 
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
            if((FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)
            {
                CPath Path ;
                Path.Combine(OriPath, strFileName) ;
                Load(hWnd, Path) ;
            }
            else
            {
                CPath Path { strFileName } ;
                CString strExt = Path.GetExtension() ; 
                if((strExt.CompareNoCase(_T(".png")) == 0) || ((strExt.CompareNoCase(_T(".jpg")) == 0)))
                {
                    m_StringList.AddTail(CurrentPath) ; 
                }
            }
        }
        if (!FindNextFile(hFind, &FindFileData))
        {
            break ;
        }
    } 
    return ; 
}