#include "pch.h"
#include <iostream>
#include<Windows.h>
#include<cstdio>
#include"File.h"
#define BUFFERSIZE 100
int main()

{
	BYTE bBuffer[BUFFERSIZE] = { 0 };
	LPVOID *ptr =(LPVOID*) bBuffer;
	CFile obj;
	if (obj.create(L"F:\\Major_project.bmp", GENERIC_READ) == TRUE)
	{
		printf("We're inside where we passsed the string and generic_read");
	}
	else
	{
		DWORD dwErrCode = GetLastError();
		printf("%d", dwErrCode);
	}
	obj.read(BUFFERSIZE - 1, *ptr);
	
	return 0;

}
