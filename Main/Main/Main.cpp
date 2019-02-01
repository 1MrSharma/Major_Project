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
	WCHAR error_message;
	CFile obj_file_to_read,obj_file_to_write;
	CError obj_error_handler;
	
	if (obj_file_to_read.create(L"F:\\Major_project.bmp", GENERIC_READ) == TRUE)
	{
		printf("File opened successfully.\n");
	}
	else
	{
		error_message=obj_error_handler.geterror();
		printf("The error message:-%c\n", error_message);
	}
	if (obj_file_to_read.read(&ptr,CFile::m_knSECTORSIZE ) == TRUE)
	{
		printf("Data stored successfully.\n");
	}
	else
	{
		error_message=obj_error_handler.geterror();
		printf("The error message:-%c\n", error_message);
	}/*
	if (obj_file_to_write.write(&ptr1,CFile::m_knSECTORSIZE) == TRUE)
	{
		printf("Data written successfully.\n");
	}
	else
	{
		error_message=obj_error_handler.geterror();
		printf("The error message:-%c\n", error_message);
	}*/
	return 0;
}
