#include "pch.h"
#include <iostream>
#include<Windows.h>
#include<cstdio>
#include"File.h"
#define BUFFERSIZE 100
int main()

{
	BYTE bBuffer[BUFFERSIZE] = { 0 };
	LPVOID *ptr = bBuffer;
	CFile obj;
	if (obj.create(L"F:\\Major_project.bmp", GENERIC_READ) == TRUE)
	{

	}
	else
	{
		GetLastError()
	}
	if (obj.read(BUFFERSIZE - 1, &ptr) == TRUE)
	{

	}
	else
	{

	}
	return 0;

}
