#include "pch.h"
#include "Error.h"
#include<cstdio>
#include <tchar.h>

LPCTSTR CError::fngeterrordescription(const DWORD dwErrCode)
{
	fnsetErrCode(dwErrCode);
	return fngeterrordescription();
}

LPCTSTR CError::fngeterrordescription(void)
{
	DWORD dwChar;
	TCHAR szmessageBuffer[512] = {NULL};
	if (m_dwErrCode)
	{
		dwChar = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM , NULL, m_dwErrCode, LANG_USER_DEFAULT, szmessageBuffer, NULL, NULL);
		if (0 == dwChar)
		{
			return _T("Failed to retrieve the error code.");
		}
		return szmessageBuffer;
	}
}

void CError::fnsetErrCode(const DWORD dwErrCode)
{
	m_dwErrCode = dwErrCode;
}

DWORD CError::fngetErrCode()
{
	return m_dwErrCode;
}