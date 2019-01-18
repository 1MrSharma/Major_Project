#include "pch.h"
#include "File.h"

HANDLE CFile::create(LPCTSTR szFileName,DWORD dwDesiredAccess,DWORD dwShareMode) {

	m_szFileName = szFileName;

	m_hFile = CreateFile(m_szFileName, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	return m_hFile;
}