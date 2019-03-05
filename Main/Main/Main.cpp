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
	CFile obj_file_to_read;
	CError obj_error_handler;

	BMPstructure *pBMPstructure = new BMPstructure;
	CBMP obj_BMP;
	DWORD dwErrCode;
				
	if (obj_file_to_read.create(L"I:\\24_bit_bitmap.bmp", GENERIC_READ, OPEN_EXISTING) == FALSE)
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
	if (obj_BMP.checkFiletype() == TRUE)
	{

		printf("Valid BMP file.\n");
		printf("Size of BMP file(in bytes):%d.\n", obj_BMP.returnSizeBMP());
		printf("Offset pixel array:%d\n", obj_BMP.returnOffsetpixelarray());
		printf("Size of Bitmap info header:%d\n", obj_BMP.returnSizebitmapinfoheader());
		printf("Bitmap width in pixels:%d.\n", obj_BMP.returnBitamapwidth());
		printf("Bitmap height in pixels:%d.\n", obj_BMP.returnBitmapheight());
		printf("Color planes:%d.\n", obj_BMP.returnColorplanes());
		printf("Color depth(bits per pixel):%d.\n", obj_BMP.returnColordepth());
		if (obj_BMP.returnCompressionmethod() == 0)
		{
			printf("Value:0\tIdentified by:BI_RGB\tCompression method:None\tComments:Most commonly used.\n");
		}
		if (obj_BMP.returnCompressionmethod() == 1)
		{
			printf("Value:1\tIdentified by:BI_RLE8\tCompression method:RLE 8-bit/pixel\tComments:Only with 8-bit/pixel bitmaps.\n");
		}
		if (obj_BMP.returnCompressionmethod() == 2)
		{
			printf("Value:2\tIdentified by:BI_RLE4\tCompression method:RLE 4-bit/pixel\tComments:Can be used only with 4-bit/pixel bitmaps.\n");
		}
		if (obj_BMP.returnCompressionmethod() == 3)
		{
			printf("Value:3\tIdentified by:BI_BITFIELDS\tCompression method:OS22XBITMAPHEADER: Huffman 1D\tComments:Only for OS/2 2.x or later.\n");
		}
		if (obj_BMP.returnCompressionmethod() == 4)
		{
			printf("Value:4\tIdentified by:BI_JPEG\tCompression method:OS22XBITMAPHEADER: RLE-24\tComments:Only for OS/2 2.x or later & for Windows NT 4.0 and 95 or later (i.e) 'BITMAPV4INFOHEADER+' JPEG image for printing.\n");
		}
		if (obj_BMP.returnCompressionmethod() == 5)
		{
			printf("Value:5/tIdentified by:BI_PNG\tCompression method:None\tComments:For Windows NT 4.0 and 95 or later (i.e) 'BITMAPV4INFOHEADER+' PNG image for printing\n");
		}
		if (obj_BMP.returnCompressionmethod() == 6)
		{
			printf("Value:6\tIdentified by:BI_ALPHABITFIELDS\tCompression method:RGBA bit field masks\tComments:Only for Windows CE 5.0 with .NET 4.0 or later\n");
		}
		if (obj_BMP.returnCompressionmethod() == 11)
		{
			printf("Value:11\tIdentified by:BI_CMYK\tCompression method:None/tComments:Only for Windows Metafile CMYK\n");
		}
		if (obj_BMP.returnCompressionmethod() == 12)
		{
			printf("Value:12\tIdentified by:BI_CMYKRLE8\tCompression method:RLE-8\tComments:Only Windows Metafile CMYK\n");
		}
		if (obj_BMP.returnCompressionmethod() == 13)
		{
			printf("Value:13\tIdentified by:BI_CMYKRLE4\tCompression method:RLE-4\tComments:only Windows Metafile CMYK\n");
		}
		printf("Size of the raw bitmap data:%d\n", obj_BMP.returnRawimagesize());
		printf("Horizontal resolution(pixel per meter):%d\n", obj_BMP.returnHorizontalresolution());
		printf("Vertical resolution(pixel per meter):%d\n", obj_BMP.returnVerticalresolution());
		printf("Number of colors in color pallete:%d\n", obj_BMP.returnColorpallete());
		printf("Important colors used:%d", obj_BMP.returnImportantcolors());
		
	}
	else
	{
		printf("Not valid BMP file.\n");
	}
	return 0;
}

