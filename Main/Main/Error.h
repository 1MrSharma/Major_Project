#pragma once
#include<Windows.h>
class CError
{
private:
	DWORD m_dwErrCode;
	
public:
	LPCTSTR fngeterrordescription(void);
	LPCTSTR fngeterrordescription(DWORD);
	void fnsetErrCode(DWORD);
	DWORD fngetErrCode(void);
};

