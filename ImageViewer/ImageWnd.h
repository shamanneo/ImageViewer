#pragma once

class CImageWnd : public CWindowImpl<CImageWnd>
{ 
	public :
		DECLARE_WND_CLASS(_T("ImageWnd"))
		
		BEGIN_MSG_MAP(CImageWnd)
			MESSAGE_HANDLER(WM_PAINT, OnPaint)
		END_MSG_MAP()
	public :
		LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) ;
} ;

