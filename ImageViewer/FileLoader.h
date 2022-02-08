#pragma once

class CFileLoader
{ 
	private :
		CWindow m_TreeView ; 
		TVINSERTSTRUCT m_tvis ; 
	public :
		CFileLoader(CWindow &TreeView) ; 
		~CFileLoader() ; 
	public :
		bool IsImageFile(CString str) ;
		void LoadFiles(CPath &Path, HTREEITEM hParentItem = TVI_ROOT) ; 
		void InsertTreeView(CPath &Path, WIN32_FIND_DATA &FindFileData, HTREEITEM &hParentItem) ;
		void InsertListView(CPath &Path, WIN32_FIND_DATA &FindFileData, HTREEITEM &hParentItem) ;
} ;
