#pragma once
#include<Windows.h>
class CFile
{
private:
	HANDLE m_hFile;
	LPCTSTR m_szFileName;
public:
	BOOL create(LPCTSTR,DWORD);
	void close();
	BOOL read( LPVOID, INT);
	BOOL write(LPVOID,INT);
	inline void setHandle(HANDLE);
	inline HANDLE getHandle()const;
};