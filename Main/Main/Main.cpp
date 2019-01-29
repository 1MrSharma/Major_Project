#include "pch.h"
#include <iostream>
#include<Windows.h>
#include<cstdio>
#include"File.h"
#define BUFFERSIZE 1000
int main()

{
	BYTE bBuffer[BUFFERSIZE] = { 0 };
	LPVOID *ptr =(LPVOID*) bBuffer;
	CFile obj;
	int a = 2;
	if (obj.create(L"F:\\Major_project.bmp", GENERIC_READ) == TRUE)
	{
		obj.read( &ptr, BUFFERSIZE - 1);
		obj.write( &ptr, a );
	}
	else
	{
		obj.geterror();
	}
	return 0;
}
