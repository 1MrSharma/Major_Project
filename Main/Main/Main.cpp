#include "pch.h"
#include <iostream>
#include<Windows.h>
#include<cstdio>
#include"File.h"
#include"Error.h"
#include"BMPstructure.h"
#include"BMP.h"
#include <tchar.h>
const int nBUFFERSIZE = 1024;
using namespace std;
int main(int argc, TCHAR *argv[])
{
	_tprintf(_T("---------------------------------------------------------------------------------------------\n"));
	_tprintf(_T("------------------------------BITMAP IMAGE RECOGNITION SOFTWARE------------------------------"));
	_tprintf(_T("\n---------------------------------------------------------------------------------------------"));

	if (argc < 3)
	{
		_tprintf(_T("\n\tUsage: <Main> <source bitmap file> <destination bitmap file> "));
		_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
		return EXIT_FAILURE;
	}
	BYTE bReadBuffer[nBUFFERSIZE] = { 0 };
	CFile obj_file_to_read, obj_file_to_write;
	CError obj_error_handler;
	BMPstructure *pBMPstructure = new BMPstructure;
	CBMP obj_BMP;
	DWORD dwErrCode;


	if (obj_file_to_read.create(argv[1], GENERIC_READ, OPEN_EXISTING) == FALSE)
	{
		_tprintf(_T("\n\tCheck for source image existence."));
		dwErrCode = GetLastError();
		_tprintf(_T("\n\tError message:%s"), obj_error_handler.geterrordescription(dwErrCode));
		_tprintf(_T("\n\tError code:%d"), obj_error_handler.getErrCode());
		_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
		return EXIT_FAILURE;
	}
	
	if (obj_file_to_read.read(bReadBuffer,CFile::m_knSECTORSIZE ) == FALSE)
	{
		dwErrCode = GetLastError();
		_tprintf(_T("\n\tError message:-%ws\n"), obj_error_handler.geterrordescription(dwErrCode));
		_tprintf(_T("\n\tError code %d"), obj_error_handler.getErrCode());
		_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
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
		DWORD bsizeofBMP = pBMPstructure->getSizeBMP();
		int nSectors = bsizeofBMP / CFile::m_knSECTORSIZE;
		int nAdditional = bsizeofBMP % CFile::m_knSECTORSIZE;
		if (obj_file_to_read.create(argv[1], GENERIC_READ, OPEN_EXISTING) == FALSE)
		{
			dwErrCode = GetLastError();
			_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.geterrordescription(dwErrCode));
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		if (obj_file_to_write.create(argv[2], GENERIC_WRITE, CREATE_ALWAYS) == FALSE)
		{
			dwErrCode = GetLastError();
			_tprintf(_T("\n\tThe error message:-%ws"), obj_error_handler.geterrordescription(dwErrCode));
			_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.getErrCode());
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		while (nSectors)
		{
			if (obj_file_to_read.read(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)
			{
				obj_file_to_read.close();
				obj_file_to_write.close();
				dwErrCode = GetLastError();
				_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.geterrordescription(dwErrCode));
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}
			if (obj_file_to_write.write(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)
			{
				obj_file_to_read.close();
				obj_file_to_write.close();
				dwErrCode = GetLastError();
				_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.geterrordescription(dwErrCode));
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}
			nSectors--;
		}
		if (obj_file_to_read.read(bReadBuffer, nAdditional) == FALSE)
		{
			obj_file_to_read.close();
			obj_file_to_write.close();
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE; 
		}
		if (obj_file_to_write.write(bReadBuffer, nAdditional) == FALSE)
		{
			obj_file_to_read.close();
			obj_file_to_write.close();
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		_tprintf(_T("\n\n\t\t\t\t\tValid BMP image file.\n\n"));
		_tprintf(_T("---------------------------------------------------------------------------------------------\n"));
		_tprintf(_T("\t\t\t\tInformation of BMP image file\n\n"));
		_tprintf(_T("\tSize of BMP file(in bytes) :\t\t\t%u\n"), obj_BMP.returnSizeBMP());
		_tprintf(_T("\tOffset pixel array :\t\t\t\t%d\n"), obj_BMP.returnOffsetpixelarray());
		_tprintf(_T("\tSize of Bitmap info header :\t\t\t%d\n"), obj_BMP.returnSizebitmapinfoheader());
		_tprintf(_T("\tBitmap width in pixels :\t\t\t%d\n"), obj_BMP.returnBitamapwidth());
		_tprintf(_T("\tBitmap height in pixels :\t\t\t%d\n"), obj_BMP.returnBitmapheight());
		_tprintf(_T("\tColor planes :\t\t\t\t\t%d\n"), obj_BMP.returnColorplanes());
		_tprintf(_T("\tColor depth(bits per pixel) :\t\t\t%d\n"), obj_BMP.returnColordepth());
		_tprintf(_T("\tCompression method\n"));
		if (obj_BMP.returnCompressionmethod() == 0)
		{
			_tprintf(_T("\t\tValue :\t\t\t\t\t0\n\t\tIdentified by :\t\t\t\tBI_RGB\n\t\tCompression :\t\t\t\tNone\n\t\tComments :\t\t\t\tMost commonly used.\n"));
		}
		if (obj_BMP.returnCompressionmethod() == 1)
		{
			_tprintf(_T("\t\tValue :\t\t\t\t\t1\n\t\tIdentified by :\t\t\t\tBI_RLE8\n\t\tCompression :\t\t\t\tRLE 8-bit/pixel\n\t\tComments :\t\t\t\tOnly with 8-bit/pixel bitmaps.\n"));
		}
		if (obj_BMP.returnCompressionmethod() == 2)
		{
			_tprintf(_T("\t\tValue :\t\t\t\t\t2\n\t\tIdentified by :\t\t\t\tBI_RLE4\n\t\tCompression :\t\t\t\tRLE 4-bit/pixel\n\t\tComments :\t\t\t\tCan be used only with 4-bit/pixel bitmaps.\n"));
		}
		if (obj_BMP.returnCompressionmethod() == 3)
		{
			_tprintf(_T("\t\tValue :\t\t\t\t\t3\n\t\tIdentified by :\t\t\t\tBI_BITFIELDS\n\t\tCompression :\t\t\t\tOS22XBITMAPHEADER : Huffman 1D\n\t\tComments :\t\t\t\tOnly for OS/2 2.x or later.\n"));
		}
		if (obj_BMP.returnCompressionmethod() == 4)
		{
			_tprintf(_T("\t\tValue :\t\t\t\t\t4\n\t\tIdentified by :\t\t\t\tBI_JPEG\n\t\tCompression :\t\t\t\tOS22XBITMAPHEADER : RLE-24\n\t\tComments :\t\t\t\tOnly for OS/2 2.x or later & for Windows NT 4.0 and 95 or later (i.e) 'BITMAPV4INFOHEADER+' JPEG image for printing.\n"));
		}
		if (obj_BMP.returnCompressionmethod() == 5)
		{
			_tprintf(_T("\t\tValue :\t\t\t\t\t5\n\t\tIdentified by :\t\t\t\tBI_PNG\n\t\tCompression :\t\t\t\tNone\n\t\tComments :\t\t\t\tFor Windows NT 4.0 and 95 or later (i.e) 'BITMAPV4INFOHEADER+' PNG image for printing\n"));
		}
		if (obj_BMP.returnCompressionmethod() == 6)
		{
			_tprintf(_T("\t\tValue :\t\t\t\t\t6\n\t\tIdentified by :\t\t\t\tBI_ALPHABITFIELDS\n\t\tCompression :\t\t\t\tRGBA bit field masks\n\t\tComments :\t\t\t\tOnly for Windows CE 5.0 with .NET 4.0 or later\n"));
		}
		if (obj_BMP.returnCompressionmethod() == 11)
		{
			_tprintf(_T("\t\tValue :\t\t\t\t\t11\n\t\tIdentified by :\t\t\t\tBI_CMYK\n\t\tCompression :\t\t\t\tNone\n\t\tComments :\t\t\t\tOnly for Windows Metafile CMYK\n"));
		}
		if (obj_BMP.returnCompressionmethod() == 12)
		{
			_tprintf(_T("\t\tValue :\t\t\t\t\t12\n\t\tIdentified by :\t\t\t\tBI_CMYKRLE8\n\t\tCompression :\t\t\t\tRLE-8\n\t\tComments :\t\t\t\tOnly Windows Metafile CMYK\n"));
		}
		if (obj_BMP.returnCompressionmethod() == 13)
		{
			_tprintf(_T("\tValue :\t\t\t\t\t13\tIdentified by :\t\t\t\tBI_CMYKRLE4\tCompression :\t\t\t\tRLE-4\tComments :\t\t\t\tonly Windows Metafile CMYK\n"));
		}
		_tprintf(_T("\tSize of the raw bitmap data  :\t\t\t%d\n"), obj_BMP.returnRawimagesize());
		_tprintf(_T("\tHorizontal resolution(pixel per meter) :\t%d\n"), obj_BMP.returnHorizontalresolution());
		_tprintf(_T("\tVertical resolution(pixel per meter) :\t\t%d\n"), obj_BMP.returnVerticalresolution());
		_tprintf(_T("\tNumber of colors in color pallete :\t\t%d\n"), obj_BMP.returnColorpallete());
		_tprintf(_T("\tImportant colors used :\t\t\t\t%d"), obj_BMP.returnImportantcolors());
		_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
	}
	else
	{
		_tprintf(_T("\n\n\t\t\t\tNot a valid BMP image file.\n"));
		_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
	}
	return 0;
}