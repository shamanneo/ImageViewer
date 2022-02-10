#pragma once
#include "ItemAttributes.h"

class CFileLoader
{ 
	private :
		TVINSERTSTRUCT m_tvis ; 
	public :
		CFileLoader() ; 
		~CFileLoader() ; 
	public :
		bool IsImageFile(CString &str) ;
		void LoadFiles(CWindow &TreeViewWnd, CWindow &ListViewWnd, ItemAttributes *pItemAttributes, HTREEITEM hParentItem) ; 
		void InsertTreeView(CWindow &TreeViewWnd, CPath &Path, WIN32_FIND_DATA &FindFileData, HTREEITEM &hParentItem) ;
		void InsertListView(CWindow &ListViewWnd, WIN32_FIND_DATA &FindFileData) ;
} ;
