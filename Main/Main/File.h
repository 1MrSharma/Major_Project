#pragma once
#include<Windows.h>
class CFile
{
private:
	HANDLE m_hFile;
	LPCTSTR m_szFileName;
public:
	static const INT m_knSECTORSIZE = 512;
public:
	BOOL fnCreate(LPCTSTR,DWORD,DWORD);
	void fnClose();
	BOOL fnRead( LPVOID, INT);
	BOOL fnWrite(LPVOID, INT);
	inline void fnSetHandle(HANDLE);
	inline HANDLE fnGetHandle(void)const;

};