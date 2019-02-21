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
//	CHelper obj_helper;
	BMPstructure *pBMPstructure = new BMPstructure;
	CBMP obj_BMP;
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
	INT nReadOffset = 0;
	//PROBLEM 2 &3 
	//In 2nd ReadOffset is incrementing values
	//3rd is that i have to setstructure pointer is it possible with object of the header BMPstructure 
	memcpy(&(pBMPstructure->m_wFiletype), bReadBuffer + nReadOffset, 2); nReadOffset += 2;
	memcpy(&(pBMPstructure->m_dwSizeBMP), bReadBuffer + nReadOffset, 4); nReadOffset += 4;
	memcpy(&(pBMPstructure->m_wReserved1), bReadBuffer + nReadOffset, 2); nReadOffset += 2;
	memcpy(&(pBMPstructure->m_wReserved2), bReadBuffer + nReadOffset, 2); nReadOffset += 2;
	memcpy(&(pBMPstructure->m_dwOffsetpixelarray), bReadBuffer + nReadOffset, 4); nReadOffset += 4;
	memcpy(&(pBMPstructure->m_dwSizebitmapinfoheader), bReadBuffer + nReadOffset, 4); nReadOffset += 4;
	memcpy(&(pBMPstructure->m_nBitmapwidth), bReadBuffer + nReadOffset, 4); nReadOffset += 4;
	memcpy(&(pBMPstructure->m_nBitmapheight), bReadBuffer + nReadOffset, 4); nReadOffset += 4;
	memcpy(&(pBMPstructure->m_wColorplanes), bReadBuffer + nReadOffset, 2); nReadOffset += 2;
	memcpy(&(pBMPstructure->m_wColordepth), bReadBuffer + nReadOffset, 2); nReadOffset += 2;
	memcpy(&(pBMPstructure->m_dwCompressionmethod), bReadBuffer + nReadOffset, 4); nReadOffset += 4;
	memcpy(&(pBMPstructure->m_dwRawimagesize), bReadBuffer + nReadOffset, 4); nReadOffset += 4;
	memcpy(&(pBMPstructure->m_dwHorizontalresolution), bReadBuffer + nReadOffset, 4); nReadOffset += 4;
	memcpy(&(pBMPstructure->m_dwVerticalresolution), bReadBuffer + nReadOffset, 4); nReadOffset += 4;
	memcpy(&(pBMPstructure->m_dwColorpallete), bReadBuffer + nReadOffset, 4); nReadOffset += 4;
	memcpy(&(pBMPstructure->m_dwImportantcolors), bReadBuffer + nReadOffset, 4); nReadOffset += 4;
	
	obj_BMP.setStructurepointer(pBMPstructure);

	//g=obj_helper.circularbyteshift(obj_BMPstructure.getFiletype/*, sizeof(&BMPstructurevariable.m_wFiletype)*/);
	//obj_BMPstructure.setFiletype(g);

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

