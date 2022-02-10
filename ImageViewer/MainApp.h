#pragma once
#include "MainWnd.h"

class CMainApp
{
    private :
        CMainWnd m_MainWnd ; 
        CWindow m_TreeView ; 
        CWindow m_ListView ; 
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
        CWindow &GetTreeViewWnd() ; 
        CWindow &GetListViewWnd() ; 
    public :
        void SetTreeViewWnd(CWindow &TreeView) ; 
        void SetListViewWnd(CWindow &ListView) ; 
} ; 

//      getter

inline CWindow &CMainApp::GetTreeViewWnd() 
{
    return m_TreeView ; 
}

inline CWindow &CMainApp::GetListViewWnd() 
{
    return m_ListView ; 
}

//      setter

inline void CMainApp::SetTreeViewWnd(CWindow &TreeView)
{
    m_TreeView = TreeView ; 
}

inline void CMainApp::SetListViewWnd(CWindow &ListView)
{
    m_ListView = ListView ; 
}