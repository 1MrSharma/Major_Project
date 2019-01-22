#include "pch.h"
#include "File.h"
#include<cstdio>
void CFile::create(LPCTSTR szFileName) 
{

	m_szFileName = szFileName;

	m_hFile = CreateFile(m_szFileName, GENERIC_ALL, FILE_SHARE_READ|FILE_SHARE_DELETE|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
}

void CFile::settr(HANDLE hFile)
{
	BOOL WINAPI CloseHandle(
		_In_ HANDLE hFile
	);
}

HANDLE CFile::gettr()
{
	return m_hFile;
}