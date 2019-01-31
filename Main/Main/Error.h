#pragma once
#include<Windows.h>
class CError
{
private:
	DWORD m_dwErrCode;
	WCHAR m_wszMsgBuffer[512];
	DWORD m_dwChar;
public:
	void geterror(void);
	void printerrormessege(DWORD);
};

