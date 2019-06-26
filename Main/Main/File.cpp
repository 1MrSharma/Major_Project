#include "pch.h"
#include "File.h"

BOOL CFile::fnCreate(const LPCTSTR szFileName,DWORD dwDesiredAccess,DWORD dwcreationdisposition) 
{
	HANDLE hFile = NULL;
	
	hFile = CreateFile(szFileName, dwDesiredAccess, FILE_SHARE_READ|FILE_SHARE_DELETE|FILE_SHARE_WRITE, NULL, dwcreationdisposition, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;
	m_szFileName = szFileName;
	fnSetHandle(hFile);
	return TRUE;
}

void CFile::fnClose()
{
	CloseHandle(m_hFile);
	m_hFile = NULL;
}

void CFile::fnSetHandle(const HANDLE hFile)
{
	m_hFile = hFile;
	
}

HANDLE CFile::fnGetHandle()//inline HANDLE CFile::fnGetHandle()const
{
	return m_hFile;
}

BOOL CFile::fnRead(LPVOID address,const INT limit)
{
	DWORD dwByteRead;
	if (FALSE == (ReadFile(m_hFile, address, limit, &dwByteRead, NULL)))
	{
		fnClose();
		return FALSE;
	}
	else
	{
		return TRUE;
	}

}

BOOL CFile::fnWrite(LPVOID address, INT limit)
{
	DWORD dwByteWrite;
	if (FALSE == (WriteFile(m_hFile, address, limit, &dwByteWrite, NULL)))
	{
		fnClose();
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

