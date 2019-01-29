#include "pch.h"
#include <iostream>
#include<Windows.h>
#include<cstdio>
#include"File.h"
#define BUFFERSIZE 1000 
int main()

{
	BYTE bBuffer[BUFFERSIZE] = { 0 };
	LPVOID ptr =(LPVOID) bBuffer;
	CFile obj;
	int SECTORSIZE = 512;
	if (obj.create(L"F:\\Major_project.bmp", GENERIC_READ) == TRUE)
	{
		
	}
	else
	{
		obj.geterror();
	}
	if (obj.read(&ptr, SECTORSIZE) == TRUE)
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
