#include "pch.h"
#include <iostream>
#include<Windows.h>
#include<cstdio>
#include"File.h"
#include"Error.h"
#include"BMPstructure.h"
const int nBUFFERSIZE = 1024;
int main()

{
	BYTE bReadBuffer[nBUFFERSIZE] = { 0 };
	CFile obj_file_to_read,obj_file_to_write;
	CError obj_error_handler;
	DWORD dwErrCode;
	
	if (obj_file_to_read.create(L"I:\\Major_project.bmp", GENERIC_READ, OPEN_EXISTING) == FALSE)
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

	memcpy(&BMPstructurevariable.m_wFiletype, bReadBuffer, 2);
	memcpy(&BMPstructurevariable.m_dwSizeBMP, bReadBuffer+2, 4);
	memcpy(&BMPstructurevariable.m_wReserved1, bReadBuffer + 6, 2);
	memcpy(&BMPstructurevariable.m_wReserved2, bReadBuffer + 8, 2);
	memcpy(&BMPstructurevariable.m_dwOffsetpixelarray, bReadBuffer + 10, 4);
	memcpy(&BMPstructurevariable.m_dwSizebitmapinfoheader, bReadBuffer + 14, 4);
	memcpy(&BMPstructurevariable.m_nBitmapwidth, bReadBuffer + 18, 4);
	memcpy(&BMPstructurevariable.m_nBitmapheight, bReadBuffer + 22, 4);
	memcpy(&BMPstructurevariable.m_wColorplanes, bReadBuffer + 26, 2);
	memcpy(&BMPstructurevariable.m_wColordepth, bReadBuffer + 28, 2);	
	memcpy(&BMPstructurevariable.m_dwCompressionmethod, bReadBuffer + 30, 4);
	memcpy(&BMPstructurevariable.m_dwRawimagesize, bReadBuffer + 34, 4);
	memcpy(&BMPstructurevariable.m_dwHorizontalresolution, bReadBuffer + 38, 4);
	memcpy(&BMPstructurevariable.m_dwVerticalresolution, bReadBuffer + 42, 4);
	memcpy(&BMPstructurevariable.m_dwColorpallete, bReadBuffer + 46, 4);
	memcpy(&BMPstructurevariable.m_dwImportantcolors, bReadBuffer + 50, 4);

	if (obj_file_to_write.create(L"I:\\WrittenFile.txt", GENERIC_WRITE, CREATE_NEW) == FALSE)
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