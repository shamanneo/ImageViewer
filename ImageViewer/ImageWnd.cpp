#include "pch.h"
#include "MainApp.h"
#include "ImageWnd.h"

CImageWnd::CImageWnd()
{

}

CImageWnd::~CImageWnd()
{

}

LRESULT CImageWnd::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL &/*bHandled*/)
{
	PAINTSTRUCT ps ; 
	HDC hDC = BeginPaint(&ps) ; 

    DrawImage(hDC) ; 

    // to do...

	EndPaint(&ps) ; 
	return 0 ; 
}

void CImageWnd::DrawImage(HDC hDC) 
{
    Gdiplus::Graphics grfx { hDC } ; 
    Gdiplus::Image Img { CMainApp::GetInstance().GetFileName() } ; 
    INT nWidth = Img.GetWidth() / 3 ; 
    INT nHeight = Img.GetHeight() / 3 ; 
    grfx.DrawImage(&Img, 100, 10, nWidth, nHeight) ; 
    return ; 
}