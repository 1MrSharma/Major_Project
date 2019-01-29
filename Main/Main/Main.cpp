#include "pch.h"
#include <iostream>
#include<Windows.h>
#include<cstdio>
#include"File.h"
const int nBUFFERSIZE = 1024;
int main()

{
	BYTE bBuffer[nBUFFERSIZE] = { 0 };
	LPVOID ptr =(LPVOID) bBuffer;
	CFile obj;
	
	if (obj.create(L"F:\\Major_project.bmp", GENERIC_READ) == TRUE)
	{
		
	}
	else
	{
		obj.geterror();
	}
	if (obj.read(&ptr,const INT CFile::nSECTORSIZE) == TRUE)
	{

	}
	else
	{
		obj.geterror();
	}
	if (obj.write(&ptr, SECTORSIZE) == TRUE)
	{

	}
	else
	{
		obj.geterror();
	}
	return 0;
}
