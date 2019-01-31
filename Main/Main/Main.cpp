#include "pch.h"
#include <iostream>
#include<Windows.h>
#include<cstdio>
#include"File.h"
#include"Error.h"

const int nBUFFERSIZE = 1024;
int main()

{
	BYTE bReadBuffer[nBUFFERSIZE] = { 0 }, bWriteBuffer[nBUFFERSIZE] = { 0 };
	LPVOID ptr = (LPVOID)bReadBuffer;
	LPVOID ptr1 = (LPVOID)bWriteBuffer;
	CFile obj_file_to_read,obj_file_to_write;
	CError obj_error_handler;
	
	if (obj_file_to_read.create(L"F:\\Major_project.bmp", GENERIC_READ) == TRUE)
	{
		printf("File opened successfully.\n");
	}
	else
	{
		obj_error_handler.geterror();
	}
	if (obj_file_to_read.read(&ptr,CFile::m_knSECTORSIZE ) == TRUE)
	{
		printf("Data stored successfully.\n");
	}
	else
	{
		obj_error_handler.geterror();
	}
	if (obj_file_to_write.write(&ptr1,CFile::m_knSECTORSIZE) == TRUE)
	{
		printf("Data written successfully.\n");
	}
	else
	{
		obj_error_handler.geterror();
	}
	return 0;
}
