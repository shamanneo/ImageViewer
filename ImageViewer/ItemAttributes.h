#pragma once

struct ItemAttributes
{
	bool m_bExpanded ; 
	CPath m_MyPath ; 
	WIN32_FIND_DATA m_FindFileData ; 

	ItemAttributes() 
	{
		m_bExpanded = false ; 
	}
} ; 