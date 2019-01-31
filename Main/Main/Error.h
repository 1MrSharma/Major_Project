#pragma once
#include<Windows.h>
class CError
{
private:
	DWORD m_dwErrCode;
	WCHAR m_wszMsgBuffer[512];
	DWORD m_dwChar;
public:
	TCHAR geterror(void);
	DWORD printerrormessege(DWORD);
};

