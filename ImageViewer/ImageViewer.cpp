#include "pch.h"
#include "MainApp.h"
#include "ImageViewer.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE /*hPrevInstance*/,
                     _In_ LPWSTR    /*lpCmdLine*/,
                     _In_ int       nCmdShow)
{
    CMainApp &MainApp = CMainApp::GetInstance() ; 
    int nResult = MainApp.Run(hInstance, nCmdShow) ;  
    CMainApp::Release() ;

    return nResult ; 
}