#pragma once
#include "resource.h"

class CMainWnd : public CWindowImpl<CMainWnd> 
{
    private :
        CWindow m_TreeView ;     
        CWindow m_ListView ;
    public :
        CMainWnd() ; 
        ~CMainWnd() ; 
    public :
        DECLARE_WND_CLASS(_T("ImageViwer"))

        BEGIN_MSG_MAP(CMainWnd)
            MESSAGE_HANDLER(WM_COMMAND, OnCommand)
            MESSAGE_HANDLER(WM_CREATE, OnCreate)
            MESSAGE_HANDLER(WM_PAINT, OnPaint) 
            MESSAGE_HANDLER(WM_SIZE, OnSize) 
            MESSAGE_HANDLER(WM_DESTROY, OnDestroy) 
            NOTIFY_HANDLER(IDC_MAIN_TREE_VIEW, TVN_SELCHANGED, OnSelectedChanged) 
            NOTIFY_HANDLER(IDC_MAIN_TREE_VIEW, TVN_DELETEITEM, OnDeleteItem) 
            NOTIFY_HANDLER(IDC_MAIN_LIST_VIEW, LVN_GETDISPINFO, OnGetDispInfo) 
        END_MSG_MAP() 
    public :
        LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) ;
        LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) ;
        LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) ;
        LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) ; 
    public :
        LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) ;
        LRESULT OnSelectedChanged(int idCtrl, LPNMHDR pNHDR, BOOL &bHandled) ; 
        LRESULT OnDeleteItem(int idCtrl, LPNMHDR pNHDR, BOOL &bHandled) ; 
        LRESULT OnGetDispInfo(int idCtrl, LPNMHDR pNHDR, BOOL &bHandled) ; 
    public :
        void CreateTreeView(RECT &rc) ; 
        void CreateListView(RECT &rc) ; 
} ;

