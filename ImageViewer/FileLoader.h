#pragma once

class CFileLoader
{ 
	private :
		TVINSERTSTRUCT m_tvis ; 
	public :
		CFileLoader() ; 
		~CFileLoader() ; 
	public :
		bool IsImageFile(CString str) ;
		void LoadFiles(CWindow &TreeViewWnd, CWindow &ListViewWnd, CPath &Path, HTREEITEM hParentItem = TVI_ROOT) ; 
		void InsertTreeView(CWindow &TreeViewWnd, CPath &Path, WIN32_FIND_DATA &FindFileData, HTREEITEM &hParentItem) ;
		void InsertListView(CWindow &ListViewWnd, CPath &Path, WIN32_FIND_DATA &FindFileData) ;
		void ClearListView(CWindow &ListViewWnd) ; 
} ;
