#pragma once 
#include<Windows.h>
class CFile
{
private:
	HANDLE m_hFile;
	LPCTSTR m_szFileName;
	
	DWORD m_cdwDesiredAccess;
	DWORD m_dwShareMode;
public:
	HANDLE create(LPCTSTR,DWORD,DWORD);

};


