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
		dwChar = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, m_dwErrCode, 0, szmessageBuffer, 512, NULL);//512 --->sizeof
		if (0 == dwChar)
		{
			return L"Failed to retrieve the error code.";
		}
		return szmessageBuffer;
	}
}

void CError::setErrCode(DWORD dwErrCode)
{
	m_dwErrCode = dwErrCode;
}

DWORD CError::getErrCode()
{
	return m_dwErrCode;
}