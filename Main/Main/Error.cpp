#include "pch.h"
#include "Error.h"
#include<cstdio>

void CError::geterror(void)
{
	m_dwErrCode =GetLastError();
	printerrormessege(m_dwChar);
}

void CError::printerrormessege(DWORD)
{
	m_dwChar = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, m_dwErrCode, 0, m_wszMsgBuffer, 512, NULL);
	printf("Error value: %d Message: %ws\n", m_dwErrCode, m_dwChar ? m_wszMsgBuffer : L"Error message not found");
}