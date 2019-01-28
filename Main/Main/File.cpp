#include "pch.h"
#include "File.h"
#include<cstdio>

BOOL CFile::create(LPCTSTR szFileName,DWORD dwDesiredAccess) 
{
	HANDLE hFile = NULL;
	m_szFileName = szFileName;
	hFile = CreateFile(m_szFileName, dwDesiredAccess, FILE_SHARE_READ|FILE_SHARE_DELETE|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;
	
	
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
		printf("Terminal failure: Unable to read from file.\n GetLastError=%08x\n", GetLastError());
		close();
		return EXIT_FAILURE;
	}

}

BOOL CFile::write(LPVOID address, INT towrite)
{
	DWORD dwByteWrite;
	if (FALSE == (WriteFile(m_hFile, address, towrite, &dwByteWrite, NULL)))
	{
		printf("Terminal failure: Unable to write to file.\n GetLastError=%08x\n", GetLastError());
		close();
		return EXIT_FAILURE;
	}
}