#include "pch.h"
#include "Error.h"
#include<cstdio>
#include <tchar.h>

#include<Windows.h>

#include<string>
using namespace std;

LPCTSTR CError::fngeterrordescription(const DWORD dwErrCode)
{
	
	fnsetErrCode(dwErrCode);
	
	return fngeterrordescription();
		
}
LPCTSTR CError::fngeterrordescription(){
	HLOCAL hlocal = NULL;
	// Get the error code's textual description
	BOOL fOk = FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL, m_dwErrCode, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
		(PTSTR)&hlocal, 0, NULL);

	if (FALSE == fOk)
		szErrorString = _TEXT("failed to retrieve system error");
	else
		szErrorString = std::string((TCHAR *)hlocal);
	return szErrorString.c_str();
	}

void CError::fnsetErrCode(const DWORD dwErrCode)
{
	m_dwErrCode = dwErrCode;
}

DWORD CError::fngetErrCode()
{
	return m_dwErrCode;
}

std::string CError::getErrorString()
{
	return szErrorString;
}