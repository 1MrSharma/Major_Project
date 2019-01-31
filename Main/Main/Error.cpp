#include "pch.h"
#include "Error.h"
#include<cstdio>

WCHAR CError::geterror(void)
{
	m_dwErrCode = GetLastError();
	if (m_dwErrCode)
	{
		m_dwChar = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, m_dwErrCode, 0, NULL, 512, NULL);
		if (m_dwChar)
		{
			//return 
		}
		else
		{
			HINSTANCE hInst;

			hInst = LoadLibrary(L"Ntdsbmsg.dll");
			if (NULL == hInst)
			{
				exit(1);
			}
			else
			{
				m_dwChar = FormatMessage(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS, hInst, m_dwErrCode, 0, m_wszMsgBuffer, 512, NULL);
					FreeLibrary( hInst ) ;
					//return
			}
		}
	}
}
