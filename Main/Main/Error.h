#pragma once
#include<Windows.h>
class CError
{
private:
	DWORD m_dwErrCode;
	
public:
	LPCTSTR geterrordescription(void);
	LPCTSTR geterrordescription(DWORD);
	void setErrCode(DWORD);
	DWORD getErrCode(void);
};

