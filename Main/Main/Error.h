#pragma once
#include<Windows.h>
class CError
{
private:
	DWORD m_dwErrCode;
	CHAR m_szErrName;
public:
	DWORD geterror(void);
};

