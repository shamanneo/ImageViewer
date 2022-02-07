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
		void LoadFiles(CPath &Path) ; 
} ;
