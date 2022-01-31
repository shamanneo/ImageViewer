#pragma once
#include "MainWnd.h"

class CMainApp
{
    private :
        CMainWnd m_MainWnd ; 
    public :
        CMainApp() ; 
        ~CMainApp() ; 
    public :
        int Run(HINSTANCE hInstance, int nCmdShow) ; 
    public :    
        static CMainApp &GetInstance() ; 
        static void Release() ; 
} ;

