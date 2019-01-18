#include "pch.h"
#include "File.h"

HANDLE CFile::create(LPCTSTR szFileName) {

	m_szFileName = szFileName;

	m_hFile = CreateFile(m_szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	return m_hFile;
}