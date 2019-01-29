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
	CFile obj;
	CError obj1;
	
	if (obj.create(L"F:\\Major_project.bmp", GENERIC_READ) == TRUE)
	{
		
	}
	else
	{
		obj1.geterror();
	}
	if (obj.read(&ptr,CFile::nSECTORSIZE ) == TRUE)
	{

	}
	else
	{
		obj1.geterror();
	}
	if (obj.write(&ptr, SECTORSIZE) == TRUE)
	{

	}
	else
	{
		obj1.geterror();
	}
	return 0;
}
