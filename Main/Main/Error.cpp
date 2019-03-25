#include "pch.h"
#include "Error.h"
#include<cstdio>


LPCTSTR CError::geterrordescription(const DWORD dwErrCode)
{
	setErrCode(dwErrCode);
	return geterrordescription();
}

LPCTSTR CError::geterrordescription(void)
{
	DWORD dwChar;
	wchar_t szmessageBuffer[512] = {NULL};
	if (m_dwErrCode)
	{
		dwChar = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, m_dwErrCode, LANG_SYSTEM_DEFAULT | LANG_USER_DEFAULT, (LPTSTR)&szmessageBuffer, NULL, NULL);
		if (0 == dwChar)
		{
			return L"Failed to retrieve the error code.";
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