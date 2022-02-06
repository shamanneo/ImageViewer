#pragma once

class CFileLoader
{ 
	private :
		CAtlList<CString> m_StringList ; 
		CWindow m_TreeView ; 
		TVINSERTSTRUCT m_tvis ; 
	public :
		CFileLoader(CWindow &TreeView) ; 
		~CFileLoader() ; 
	public :
		bool IsImageFile(CString str) ; 
		void Load(HWND hWnd, CPath &CurrentPath, HTREEITEM hTreeItem) ; // control window.
} ;

