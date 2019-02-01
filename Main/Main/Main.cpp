#include "pch.h"
#include <iostream>
#include<Windows.h>
#include<cstdio>
#include"File.h"
#include"Error.h"

const int nBUFFERSIZE = 1024;
int main()

{
	BYTE bReadBuffer[nBUFFERSIZE] = { 0 };
	CFile obj_file_to_read,obj_file_to_write;
	CError obj_error_handler;
	DWORD dwErrCode;
	
	if (obj_file_to_read.create(L"F:\\Major_project.bmp", GENERIC_READ, OPEN_EXISTING) == FALSE)
	{
		dwErrCode = GetLastError();
		printf("The error message:-%ws\n", obj_error_handler.geterrordescription(dwErrCode));
		return EXIT_FAILURE;
	}

	if (obj_file_to_read.read(bReadBuffer,CFile::m_knSECTORSIZE ) == FALSE)
	{
		dwErrCode = GetLastError();
		printf("The error message:-%ws\n", obj_error_handler.geterrordescription(dwErrCode));
		return EXIT_FAILURE;
	}
	obj_file_to_read.close();

	//printf("%s", bReadBuffer);

	if (obj_file_to_write.create(L"F:\\WrittenFile.txt", GENERIC_WRITE, CREATE_NEW) == FALSE)
	{
		dwErrCode = GetLastError();
		printf("The error message:-%ws\n", obj_error_handler.geterrordescription(dwErrCode));
		return EXIT_FAILURE;
	}
	

	if (obj_file_to_write.write(bReadBuffer, sizeof(bReadBuffer)) == FALSE)
	{
		printf("The error message:-%ws\n", obj_error_handler.geterrordescription());
		return EXIT_FAILURE;
	}
	obj_file_to_write.close();
	return 0;
}

//Write clsas diagram of BMP class.