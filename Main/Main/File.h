#pragma once //a statement to preprocessor that exexcute statement...A request topreprocessor
#include<Windows.h>
class CFile
{
private:
	HANDLE m_hFile;
	LPCTSTR m_szFileName;
public:
	HANDLE create(LPCTSTR);

};


