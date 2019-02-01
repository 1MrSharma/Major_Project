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
	CFile obj_file_to_read;
	CError obj_error_handler;
	
	if (obj_file_to_read.create(L"F:\\Major_project.bmp", GENERIC_READ) == FALSE)
	{
		printf("The error message:-%s\n", obj_error_handler.geterrordescription());
		return EXIT_FAILURE;
	}

	if (obj_file_to_read.read(bReadBuffer,CFile::m_knSECTORSIZE ) == FALSE)
	{
		printf("The error message:-%s\n", obj_error_handler.geterrordescription());
		return EXIT_FAILURE;
	}
	obj_file_to_read.close();

	printf("%s", bReadBuffer);
	return 0;
}
//Have to write
//Write clsas diagram of BMP class.