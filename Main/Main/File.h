#pragma once
#include<Windows.h>
class CFile
{
private:
	HANDLE m_hFile;
	LPCTSTR m_szFileName;
	
public:
	static const INT m_knSECTORSIZE = 512;
	BOOL create(LPCTSTR,DWORD);
	void close();
	BOOL read( LPVOID, INT);
	BOOL write(LPVOID, INT);
	inline void setHandle(HANDLE);
	inline HANDLE getHandle(void)const;
};