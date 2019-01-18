#include "pch.h"
#include "File.h"
#include<cstdio>
HANDLE CFile::create(LPCTSTR szFileName,DWORD dwDesiredAccess,DWORD dwShareMode) {

	m_szFileName = szFileName;

	m_hFile = CreateFile(m_szFileName, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	return m_hFile;
}

void CFile::sethandle(HANDLE hFile)
{
	m_hFile = hFile;
}
HANDLE CFile::gethandle()
{
	return m_hFile;
}

/*
void CFile::setr(DWORD dwDesiredAccess, DWORD dwShareMode)
{
	if (dwDesiredAccess == GENERIC_READ && dwShareMode == FILE_SHARE_READ)
	{
		
	}
}

void CFile::getr()*/
//merge the branch to major