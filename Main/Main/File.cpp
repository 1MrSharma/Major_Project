#include "pch.h"
#include "File.h"
#include<cstdio>

BOOL CFile::create(LPCTSTR szFileName,DWORD dwDesiredAccess) 
{
	HANDLE hFile = NULL;

	hFile = CreateFile(m_szFileName, dwDesiredAccess, FILE_SHARE_READ|FILE_SHARE_DELETE|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;
	
	m_szFileName = szFileName;
	setHandle(hFile);
	return TRUE;
}

void CFile::close()
{
	CloseHandle(m_hFile);
	m_hFile = NULL;
}

void CFile::setHandle(HANDLE hFile)
{
	m_hFile = hFile;
	
}

HANDLE CFile::getHandle()const
{
	return m_hFile;
}

BOOL CFile::read(INT limit, LPVOID address)
{
	DWORD dwByteRead = 0;
	if(ReadFile(m_hFile,address,limit,&dwByteRead,NULL))
}