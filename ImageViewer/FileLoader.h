#pragma once

class CFileLoader
{ 
	private :
		CAtlList<CString> m_StringList ; 
		CString m_path ; 
	public :
		CFileLoader() ; 
		~CFileLoader() ; 
	public :
		void Load(HWND hWnd, CPath &CurrentPath) ; // control window.
} ;

