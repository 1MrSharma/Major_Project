#include "pch.h"
#include "Error.h"
#include<cstdio>
#include <tchar.h>

LPCTSTR CError::geterrordescription(const DWORD dwErrCode)
{
	setErrCode(dwErrCode);
	return geterrordescription();
}

LPCTSTR CError::geterrordescription(void)
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

void CError::setErrCode(const DWORD dwErrCode)
{
	m_dwErrCode = dwErrCode;
}

DWORD CError::getErrCode()
{
	return m_dwErrCode;
}