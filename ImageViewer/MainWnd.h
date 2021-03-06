#pragma once
#include "resource.h"
#include "ImageWnd.h"

class CMainWnd : public CWindowImpl<CMainWnd> 
{
    private :
        CWindow m_TreeView ;     
        CWindow m_ListView ;
        CImageWnd m_ImageWnd ; 
    public :
        CMainWnd() ; 
        ~CMainWnd() ; 
    public :
        DECLARE_WND_CLASS(_T("ImageViewer"))

        BEGIN_MSG_MAP(CMainWnd)
            MESSAGE_HANDLER(WM_COMMAND, OnCommand)
            MESSAGE_HANDLER(WM_CREATE, OnCreate)
            MESSAGE_HANDLER(WM_PAINT, OnPaint) 
            MESSAGE_HANDLER(WM_SIZE, OnSize) 
            MESSAGE_HANDLER(WM_DESTROY, OnDestroy) 
            NOTIFY_HANDLER(IDC_MAIN_TREE_VIEW, TVN_SELCHANGED, OnSelectedChanged) 
            NOTIFY_HANDLER(IDC_MAIN_TREE_VIEW, TVN_DELETEITEM, OnDeleteTItem) 
            NOTIFY_HANDLER(IDC_MAIN_LIST_VIEW, LVN_ITEMCHANGED , OnItemChanged) 
            NOTIFY_HANDLER(IDC_MAIN_LIST_VIEW, LVN_DELETEITEM, OnDeleteLItem) 
        END_MSG_MAP() 
    public :
        LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) ;
        LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) ;
        LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) ;
        LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) ; 
    public :
        LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled) ;
        LRESULT OnSelectedChanged(int idCtrl, LPNMHDR pNHDR, BOOL &bHandled) ; 
        LRESULT OnDeleteTItem(int idCtrl, LPNMHDR pNHDR, BOOL &bHandled) ; 
        LRESULT OnItemChanged(int idCtrl, LPNMHDR pNHDR, BOOL &bHandled) ; 
        LRESULT OnDeleteLItem(int idCtrl, LPNMHDR pNHDR, BOOL &bHandled) ; 
    public :
        void CreateTreeView(RECT &rc) ; 
        void CreateListView(RECT &rc) ; 
        void Draw(CPath &Path) ; 
} ;

