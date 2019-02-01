#pragma once
#include<Windows.h>
class CError
{
private:
	DWORD m_dwErrCode;
	DWORD m_dwChar;
	WCHAR messageBuffer = NULL;
public:
	WCHAR geterror(void);
};

