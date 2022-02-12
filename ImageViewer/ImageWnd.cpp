#include "pch.h"
#include "ImageWnd.h"

LRESULT CImageWnd::OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL &/*bHandled*/)
{
	PAINTSTRUCT ps ; 
	HDC hDC = BeginPaint(&ps) ; 
	UNREFERENCED_PARAMETER(hDC) ; // to do. 
	EndPaint(&ps) ; 
	return 0 ; 
}