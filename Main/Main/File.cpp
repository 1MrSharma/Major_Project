#include "pch.h"
#include "File.h"
#include<cstdio>

BOOL CFile::create(LPCTSTR szFileName,DWORD dwDesiredAccess) 
{
	HANDLE hFile = NULL;
	
	hFile = CreateFile(szFileName, dwDesiredAccess, FILE_SHARE_READ|FILE_SHARE_DELETE|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
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

BOOL CFile::read(LPVOID address,INT limit)
{
	DWORD dwByteRead;
	if (FALSE == (ReadFile(m_hFile, address, limit, &dwByteRead, NULL)))
	{
		geterror();
		close();
		return FALSE;
	}

}

BOOL CFile::write(LPVOID address, INT towrite)
{
	DWORD dwByteWrite;
	if (FALSE == (WriteFile(m_hFile, address, towrite, &dwByteWrite, NULL)))
	{
		geterror();
		close();
		return FALSE;
	}
}

DWORD CFile::geterror(void)
{
	GetLastError();
}