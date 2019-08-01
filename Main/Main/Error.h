#pragma once
#include<Windows.h>
#include<string>
class CError
{
private:
		DWORD			 m_dwErrCode;
		std::string		 szErrorString;
public:
		LPCTSTR			fngeterrordescription();
		LPCTSTR			fngeterrordescription(DWORD);
		void			fnsetErrCode(DWORD);
		DWORD			fngetErrCode(void);
		std::string		getErrorString();
};

