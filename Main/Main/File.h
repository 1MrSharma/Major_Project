#pragma once //a statement to preprocessor that exexcute statement...A request topreprocessor
#include<Windows.h>
class CFile
{
private:
	HANDLE m_hFile;
	LPCTSTR m_szFileName;
	// Does the 2 attributes written below are really required? Question yourself  
	DWORD m_dwDesiredAccess;
	DWORD m_dwShareMode;
public:
	HANDLE create(LPCTSTR,DWORD,DWORD);
	/*void setr(HANDLE);
	 *HANDLE getr();
	 */
};


