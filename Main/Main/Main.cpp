#include "pch.h"
#include <iostream>
#include<Windows.h>
#include<cstdio>
#include"File.h"
#include"Error.h"

const int nBUFFERSIZE = 1024;
int main()

{
	BYTE bBuffer[nBUFFERSIZE] = { 0 };
	LPVOID ptr =(LPVOID) bBuffer;
	CFile obj,obj2;
	CError obj1;
	TCHAR error;
	
	if (obj.create(L"F:\\Major_project.bmp", GENERIC_READ) == TRUE)
	{
		printf("File opened successfully.\n");
	}
	else
	{
		error=obj1.geterror();
		std::cout << error << std::endl;
	}
	if (obj.read(&ptr,CFile::g_nSECTORSIZE ) == TRUE)
	{

	}
	else
	{
		obj1.geterror();
	}
	if (obj2.write(&ptr,CFile::g_nSECTORSIZE) == TRUE)
	{

	}
	else
	{
		obj1.geterror();
	}
	return 0;
}
