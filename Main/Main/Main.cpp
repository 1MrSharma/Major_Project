#include "pch.h"
#include <iostream>
#include<Windows.h>
#include<cstdio>
#include"File.h"
#include"Error.h"
#include"BMPstructure.h"
#include"BMP.h"
#include<C:\Users\Shubham Sharma\Desktop\1MrSharma\Major_Project\Main\Main\Helper.h>
const int nBUFFERSIZE = 1024;
using namespace std;
int main()

{
	BYTE bReadBuffer[nBUFFERSIZE] = { 0 };
	CFile obj_file_to_read;// , obj_file_to_write;
	CError obj_error_handler;
	CHelper obj_helper;
	BMPstructure obj_BMPstructure;
	CBMP obj_BMP;
	DWORD dwErrCode;
	WORD g;
	
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
	//INT nReadOffset = 0;
	
	obj_BMPstructure.setFiletype((WORD)memcpy(obj_BMPstructure.getFiletype, bReadBuffer, 2));
	obj_BMPstructure.setSizeBMP((DWORD)memcpy(obj_BMPstructure.getSizeBMP, bReadBuffer + 2, 4));
	obj_BMPstructure.setReserved1((WORD)memcpy(obj_BMPstructure.getReserved1, bReadBuffer + 6, 2));
	obj_BMPstructure.setReserved2((WORD)memcpy(obj_BMPstructure.getReserved2, bReadBuffer + 8, 2));
	obj_BMPstructure.setOffsetpixelarray((DWORD)memcpy(obj_BMPstructure.getOffsetpixelarray, bReadBuffer + 10, 4));
	obj_BMPstructure.setSizebitmapinfoheader((DWORD)memcpy(obj_BMPstructure.getSizebitmapinfoheader, bReadBuffer + 14, 4));
	obj_BMPstructure.setBitmapwidth((INT32)memcpy(obj_BMPstructure.getBitmapwidth, bReadBuffer + 18, 4));
	obj_BMPstructure.setBitmapheight((INT32)memcpy(obj_BMPstructure.getBitmapheight, bReadBuffer + 22, 4));
	obj_BMPstructure.setColorplanes((WORD)memcpy(obj_BMPstructure.getColorplanes, bReadBuffer + 26, 2));
	obj_BMPstructure.setColordepth((WORD)memcpy(obj_BMPstructure.getColordepth, bReadBuffer + 28, 2));
	obj_BMPstructure.setCompressionmethod((DWORD)memcpy(obj_BMPstructure.getCompressionmethod, bReadBuffer + 30, 4));
	obj_BMPstructure.setRawimagesize((DWORD)memcpy(obj_BMPstructure.getRawimagesize, bReadBuffer + 34, 4));
	obj_BMPstructure.setHorizontalresolution((DWORD)memcpy(obj_BMPstructure.getHorizontalresolution, bReadBuffer + 38, 4));
	obj_BMPstructure.setVerticalresolution((DWORD)memcpy(obj_BMPstructure.getVerticalresolution, bReadBuffer + 42, 4));
	obj_BMPstructure.setColorpallete((DWORD)memcpy(obj_BMPstructure.getColorpallete, bReadBuffer + 46, 4));
	obj_BMPstructure.setImportantcolors((DWORD)memcpy(obj_BMPstructure.getImportantcolors, bReadBuffer + 50, 4));

	g=obj_helper.circularbyteshift(obj_BMPstructure.getFiletype/*, sizeof(&BMPstructurevariable.m_wFiletype)*/);
	obj_BMPstructure.setFiletype(g);

	//Validation of BMP here
	/*if (obj_file_to_write.create(L"I:\\WrittenFile.txt", GENERIC_WRITE, CREATE_NEW) == FALSE)
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
	*/
	return 0;
}

