#pragma once
#include "MainWnd.h"

class CMainApp
{
    private :
        CMainWnd m_MainWnd ; 
        CPath m_FileName ; 
        ULONG_PTR m_gdiplusToken ; 
    public :
        CMainApp() ; 
        ~CMainApp() ; 
    public :
        int Run(HINSTANCE hInstance, int nCmdShow) ; 
    public :    
        static CMainApp &GetInstance() ; 
        static void Release() ; 
    public :
        CPath &GetFileName() ;
    public :
        void SetFileName(CPath &Path) ; 
} ; 

//      getter

inline CPath &CMainApp::GetFileName()  
{
    return m_FileName ; 
}

//      setter 

inline void CMainApp::SetFileName(CPath &Path)
{
    m_FileName = Path ; 
}