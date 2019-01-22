#pragma once
#include<Windows.h>
class CFile
{
private:
	HANDLE m_hFile;
	LPCTSTR m_szFileName;
	
	
public:
	HANDLE create(LPCTSTR);
	void settr(HANDLE);
	HANDLE gettr(HANDLE);
		
};


