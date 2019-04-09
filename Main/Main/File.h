#pragma once
#include<Windows.h>
class CFile
{
private:
	HANDLE m_hFile;
	LPCSTR m_szFileName;
public:
	static const INT m_knSECTORSIZE = 512;
public:
	BOOL create(LPCSTR,DWORD,DWORD);
	void close();
	BOOL read( LPVOID, INT);
	BOOL write(LPVOID, INT);
	inline void setHandle(HANDLE);
	inline HANDLE getHandle(void)const;
};