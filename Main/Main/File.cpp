#include "pch.h"
#include "File.h"
#include<cstdio>

BOOL CFile::create(const LPCSTR szFileName,DWORD dwDesiredAccess,DWORD dwcreationdisposition) 
{
	HANDLE hFile = NULL;
	
	hFile = CreateFileA(szFileName, dwDesiredAccess, FILE_SHARE_READ|FILE_SHARE_DELETE|FILE_SHARE_WRITE, NULL, dwcreationdisposition, FILE_ATTRIBUTE_NORMAL, NULL);
	
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

void CFile::setHandle(const HANDLE hFile)
{
	m_hFile = hFile;
	
}

HANDLE CFile::getHandle()const
{
	return m_hFile;
}

BOOL CFile::read(LPVOID address,const INT limit)
{
	DWORD dwByteRead;
	if (FALSE == (ReadFile(m_hFile, address, limit, &dwByteRead, NULL)))
	{
		close();
		return FALSE;
	}
	else
	{
		return TRUE;
	}

}

BOOL CFile::write(LPVOID address, INT limit)
{
	DWORD dwByteWrite;
	if (FALSE == (WriteFile(m_hFile, address, limit, &dwByteWrite, NULL)))
	{
		close();
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

