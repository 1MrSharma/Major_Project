#include "pch.h"
#include <iostream>
#include<tchar.h>
#include<tchar.h>
#include<cstdio>
#include<vector>
#include"Helper.h"
#include"BMP.h"
#include"File.h"
#include"Error.h"
#include"Cmdline.h"

const int nBUFFERSIZE = 1024;
using namespace std;
int main(int argc,TCHAR *argv[])
{
	CCmdLine obj_cmdline;
	int nFlagOptions = 0;
	if (obj_cmdline.fnCheckEndingCharofBMP(argv[1]) == FALSE)
	{
		return 0;
	}
	if (obj_cmdline.fnCheckOptionList(argv[2]) == FALSE)
	{
		 if (obj_cmdline.fnCheckEndingCharofBMP(argv[2]) == FALSE)
		 {
			return 0;
		 }
		 if (obj_cmdline.fnCheckOptionList(argv[3]) == FALSE)
		 {
			 return 0;
		 }
		 nFlagOptions = 1;
	}
	CBMP obj_BMP;
	CFile obj_file_to_read, obj_file_to_write;
	CError obj_error_handler;
	DWORD dwErrCode;
	BYTE bReadBuffer[nBUFFERSIZE] = { 0 };
	BMPstructure *pBMPstructure = new BMPstructure;
	obj_BMP.fnsetStructurepointer(pBMPstructure);
	if (obj_file_to_read.fnCreate(argv[1], GENERIC_READ, OPEN_EXISTING) == FALSE)
	{
		_tprintf(_T("\n\tCheck for source image existence."));
		dwErrCode = GetLastError();
		_tprintf(_T("\n\tError message:%s"), obj_error_handler.fngeterrordescription(dwErrCode));
		_tprintf(_T("\n\tError code:%d"), obj_error_handler.fngetErrCode());
		return EXIT_FAILURE;
	}
	if (obj_file_to_read.fnRead(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)
	{
		dwErrCode = GetLastError();
		_tprintf(_T("\n\tError message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
		_tprintf(_T("\n\tError code %d"), obj_error_handler.fngetErrCode());
		return EXIT_FAILURE;
	}
	obj_file_to_read.fnClose();
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
	string str[] = { _T("-h1"),_T("-h2"),_T("-i"),_T("-p"),_T("-o"),_T("-bw") };
	int nIterator;
	if (nFlagOptions == 0) {  nIterator = 2; }
	else { nIterator = 3; }
	if (str[0]==argv[nIterator])//-h1
	{
		cout << hex << obj_BMP.fnreturnFiletype()<< " "<<obj_BMP.fnreturnSizeBMP()<< " " << obj_BMP.fnreturnReserved1()<< " " << obj_BMP.fnreturnReserved2()<< " " << obj_BMP.fnreturnOffsetpixelarray();
		return 0;
	}
	if(str[1]==argv[nIterator])//-h2
	{
		cout << obj_BMP.fnreturnSizebitmapinfoheader() << " " << obj_BMP.fnreturnBitamapwidth() << " " << obj_BMP.fnreturnBitmapheight() << " " << obj_BMP.fnreturnColorplanes() << " " << obj_BMP.fnreturnColordepth() << " " << obj_BMP.fnreturnCompressionmethod() << " " << obj_BMP.fnreturnRawimagesize() << " " << obj_BMP.fnreturnHorizontalresolution() << " " << obj_BMP.fnreturnVerticalresolution() << " " << obj_BMP.fnreturnColorpallete() << " " << obj_BMP.fnreturnImportantcolors();
		return 0;
	}
	if (argv[nIterator] == str[2])//-i
	{		
		if (obj_BMP.fncheckFiletype() == TRUE)
		{
			_tprintf(_T("---------------------------------------------------------------------------------------------\n"));
			_tprintf(_T("\n\n\t\t\t\t\tValid BMP image file.\n\n"));
			_tprintf(_T("---------------------------------------------------------------------------------------------\n"));
			_tprintf(_T("\t\t\t\tInformation of BMP image file\n\n"));
			_tprintf(_T("\tSize of BMP file(in bytes) :\t\t\t%u\n"), obj_BMP.fnreturnSizeBMP());
			_tprintf(_T("\tOffset pixel array :\t\t\t%d\n"), obj_BMP.fnreturnOffsetpixelarray());
			_tprintf(_T("\tSize of Bitmap info header :\t\t\t%d\n"), obj_BMP.fnreturnSizebitmapinfoheader());
			_tprintf(_T("\tBitmap width in pixels :\t\t\t%d\n"), obj_BMP.fnreturnBitamapwidth());
			_tprintf(_T("\tBitmap height in pixels :\t\t\t%d\n"), obj_BMP.fnreturnBitmapheight());
			_tprintf(_T("\tColor planes :\t\t\t\t\t%d\n"), obj_BMP.fnreturnColorplanes());
			_tprintf(_T("\tColor depth(bits per pixel) :\t\t\t%d\n"), obj_BMP.fnreturnColordepth());
			_tprintf(_T("\tCompression method\n"));
			if (obj_BMP.fnreturnCompressionmethod() == 0)
			{
				_tprintf(_T("\t\tValue :\t\t\t\t\t0\n\t\tIdentified by :\t\t\t\tBI_RGB\n\t\tCompression :\t\t\t\tNone\n\t\tComments :\t\t\t\tMost commonly used.\n"));
			}
			if (obj_BMP.fnreturnCompressionmethod() == 1)
			{
				_tprintf(_T("\t\tValue :\t\t\t\t\t1\n\t\tIdentified by :\t\t\t\tBI_RLE8\n\t\tCompression :\t\t\t\tRLE 8-bit/pixel\n\t\tComments :\t\t\t\tOnly with 8-bit/pixel bitmaps.\n"));
			}
			if (obj_BMP.fnreturnCompressionmethod() == 2)
			{
				_tprintf(_T("\t\tValue :\t\t\t\t\t2\n\t\tIdentified by :\t\t\t\tBI_RLE4\n\t\tCompression :\t\t\t\tRLE 4-bit/pixel\n\t\tComments :\t\t\t\tCan be used only with 4-bit/pixel bitmaps.\n"));
			}
			if (obj_BMP.fnreturnCompressionmethod() == 3)
			{
				_tprintf(_T("\t\tValue :\t\t\t\t\t3\n\t\tIdentified by :\t\t\t\tBI_BITFIELDS\n\t\tCompression :\t\t\t\tOS22XBITMAPHEADER : Huffman 1D\n\t\tComments :\t\t\t\tOnly for OS/2 2.x or later.\n"));
			}
			if (obj_BMP.fnreturnCompressionmethod() == 4)
			{
				_tprintf(_T("\t\tValue :\t\t\t\t\t4\n\t\tIdentified by :\t\t\t\tBI_JPEG\n\t\tCompression :\t\t\t\tOS22XBITMAPHEADER : RLE-24\n\t\tComments :\t\t\t\tOnly for OS/2 2.x or later & for Windows NT 4.0 and 95 or later (i.e) 'BITMAPV4INFOHEADER+' JPEG image for printing.\n"));
			}
			if (obj_BMP.fnreturnCompressionmethod() == 5)
			{
				_tprintf(_T("\t\tValue :\t\t\t\t\t5\n\t\tIdentified by :\t\t\t\tBI_PNG\n\t\tCompression :\t\t\t\tNone\n\t\tComments :\t\t\t\tFor Windows NT 4.0 and 95 or later (i.e) 'BITMAPV4INFOHEADER+' PNG image for printing\n"));
			}
			if (obj_BMP.fnreturnCompressionmethod() == 6)
			{
				_tprintf(_T("\t\tValue :\t\t\t\t\t6\n\t\tIdentified by :\t\t\t\tBI_ALPHABITFIELDS\n\t\tCompression :\t\t\t\tRGBA bit field masks\n\t\tComments :\t\t\t\tOnly for Windows CE 5.0 with .NET 4.0 or later\n"));
			}
			if (obj_BMP.fnreturnCompressionmethod() == 11)
			{
				_tprintf(_T("\t\tValue :\t\t\t\t\t11\n\t\tIdentified by :\t\t\t\tBI_CMYK\n\t\tCompression :\t\t\t\tNone\n\t\tComments :\t\t\t\tOnly for Windows Metafile CMYK\n"));
			}
			if (obj_BMP.fnreturnCompressionmethod() == 12)
			{
				_tprintf(_T("\t\tValue :\t\t\t\t\t12\n\t\tIdentified by :\t\t\t\tBI_CMYKRLE8\n\t\tCompression :\t\t\t\tRLE-8\n\t\tComments :\t\t\t\tOnly Windows Metafile CMYK\n"));
			}
			if (obj_BMP.fnreturnCompressionmethod() == 13)
			{
				_tprintf(_T("\tValue :\t\t\t\t\t13\tIdentified by :\t\t\t\tBI_CMYKRLE4\tCompression :\t\t\t\tRLE-4\tComments :\t\t\t\tonly Windows Metafile CMYK\n"));
			}
			_tprintf(_T("\tSize of the raw bitmap data  :\t\t\t%d\n"), obj_BMP.fnreturnRawimagesize());
			_tprintf(_T("\tHorizontal resolution(pixel per meter) :\t%d\n"), obj_BMP.fnreturnHorizontalresolution());
			_tprintf(_T("\tVertical resolution(pixel per meter) :\t\t%d\n"), obj_BMP.fnreturnVerticalresolution());
			_tprintf(_T("\tNumber of colors in color palette :\t\t%d\n"), obj_BMP.fnreturnColorpallete());
			_tprintf(_T("\tImportant colors used :\t\t\t\t%d"), obj_BMP.fnreturnImportantcolors());
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));

		}
		else
		{
			_tprintf(_T("---------------------------------------------------------------------------------------------\n"));
			_tprintf(_T("\n\n\t\t\t\tNot a valid BMP image file.\n"));
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
		}
		return 0;
	}
	if(argv[nIterator]==str[3])//-p
	{
		DWORD bsizeofBMP = pBMPstructure->fngetSizeBMP();
		bsizeofBMP -= obj_BMP.fnreturnOffsetpixelarray();
		int nSectors = bsizeofBMP / CFile::m_knSECTORSIZE;
		int nAdditional = bsizeofBMP % CFile::m_knSECTORSIZE;
		int nFlagPixelArray = 1;
		if (obj_file_to_read.fnCreate(argv[1], GENERIC_READ, OPEN_EXISTING) == FALSE)
		{
			dwErrCode = GetLastError();
			_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		if (obj_file_to_write.fnCreate(argv[2], GENERIC_WRITE, CREATE_ALWAYS) == FALSE)
		{
			dwErrCode = GetLastError();
			_tprintf(_T("\n\tThe error message:-%ws"), obj_error_handler.fngeterrordescription(dwErrCode));
			_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		while(nSectors)
		{
			if (nFlagPixelArray == 1)
			{
				DWORD dwptr = SetFilePointer(obj_file_to_read.fnGetHandle(), obj_BMP.fnreturnOffsetpixelarray(), NULL, FILE_BEGIN);
				if (dwptr == INVALID_SET_FILE_POINTER)
				{
					dwErrCode = GetLastError();
					_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
					return EXIT_FAILURE;
				}
			}
				if (obj_file_to_read.fnRead(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)
				{
					obj_file_to_read.fnClose();
					obj_file_to_write.fnClose();
					dwErrCode = GetLastError();
					_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
					_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
					return EXIT_FAILURE;
				}
				if (obj_file_to_write.fnWrite(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)
				{
					obj_file_to_read.fnClose();
					obj_file_to_write.fnClose();
					dwErrCode = GetLastError();
					_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
					_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
					return EXIT_FAILURE;
				}
				--nFlagPixelArray;
			

			nSectors--;
		}
		if (obj_file_to_read.fnRead(bReadBuffer, nAdditional) == FALSE)
		{
			obj_file_to_read.fnClose();
			obj_file_to_write.fnClose();
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		if (obj_file_to_write.fnWrite(bReadBuffer, nAdditional) == FALSE)
		{
			obj_file_to_read.fnClose();
			obj_file_to_write.fnClose();
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}

		return 0;
	}
	if (argv[nIterator] == str[4])//-o
	{
		DWORD bsizeofBMP = pBMPstructure->fngetSizeBMP();
		int nSectors = bsizeofBMP / CFile::m_knSECTORSIZE;
		int nAdditional = bsizeofBMP % CFile::m_knSECTORSIZE;
		if (obj_file_to_read.fnCreate(argv[1], GENERIC_READ, OPEN_EXISTING) == FALSE)
		{
			dwErrCode = GetLastError();
			_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		if (obj_file_to_write.fnCreate(argv[2], GENERIC_WRITE, CREATE_ALWAYS) == FALSE)
		{
			dwErrCode = GetLastError();
			_tprintf(_T("\n\tThe error message:-%ws"), obj_error_handler.fngeterrordescription(dwErrCode));
			_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		while (nSectors)
		{
			if (obj_file_to_read.fnRead(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)
			{
				obj_file_to_read.fnClose();
				obj_file_to_write.fnClose();
				dwErrCode = GetLastError();
				_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}
			if (obj_file_to_write.fnWrite(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)
			{
				obj_file_to_read.fnClose();
				obj_file_to_write.fnClose();
				dwErrCode = GetLastError();
				_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}

			nSectors--;
		}
		if (obj_file_to_read.fnRead(bReadBuffer, nAdditional) == FALSE)
		{
			obj_file_to_read.fnClose();
			obj_file_to_write.fnClose();
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		if (obj_file_to_write.fnWrite(bReadBuffer, nAdditional) == FALSE)
		{
			obj_file_to_read.fnClose();
			obj_file_to_write.fnClose();
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		return 0;
	}
	if (argv[nIterator] == str[5])//-bw
	{
		int nBitmapImageWidth = pBMPstructure->fngetBitmapwidth();
		int nRowSize = ((nBitmapImageWidth + 31) / 32)*4;
		int nSizeRawBitmap = nRowSize * (pBMPstructure->fngetBitmapheight());
		int nSizeBMP = nSizeRawBitmap + 62;
		bReadBuffer[0] = pBMPstructure->fngetFiletype();
		bReadBuffer[2] = nSizeBMP;//Error Debugging
		bReadBuffer[6] = pBMPstructure->fngetReserved1();
		bReadBuffer[8] = pBMPstructure->fngetReserved2();
		bReadBuffer[10] = 0x3E; bReadBuffer[14] = 0x28;
		bReadBuffer[18] = nBitmapImageWidth;
		bReadBuffer[22] = pBMPstructure->fngetBitmapheight();
		bReadBuffer[26] = pBMPstructure->fngetColorplanes(); bReadBuffer[28] = 1; bReadBuffer[30] = pBMPstructure->fngetCompressionmethod();
		bReadBuffer[34] = nSizeRawBitmap;//Error Debugging
		bReadBuffer[38] = pBMPstructure->fngetHorizontalresolution(); bReadBuffer[42] = pBMPstructure->fngetVerticalresolution();
		bReadBuffer[46] = pBMPstructure->fngetColorpalette(); bReadBuffer[50] = pBMPstructure->fngetImportantcolors();
		bReadBuffer[54] = 0x00; bReadBuffer[55] = 0x00; bReadBuffer[56] = 0x00; bReadBuffer[57] = 0x00;
		bReadBuffer[58] = 0xff; bReadBuffer[59] = 0xff; bReadBuffer[60] = 0xff; bReadBuffer[61] = 0x00;
		int nLineLengthColoured, nPaddingColoured;
		int nByteBlackAndWhite, nPaddingBlackAndWhite, nLineLengthBlackAndWhite;
		if (obj_BMP.fnreturnColordepth() == 24 )//8,16
		{
			if (((obj_BMP.fnreturnBitamapwidth() * (obj_BMP.fnreturnColordepth() / 8)) % 4) != 0)
			{
				nPaddingColoured = 4 - ((obj_BMP.fnreturnBitamapwidth() * (obj_BMP.fnreturnColordepth()) / 8) % 4);
			}
			else 
			{
				nPaddingColoured = 0;
			}
			nLineLengthColoured = (obj_BMP.fnreturnBitamapwidth() * (obj_BMP.fnreturnColordepth() / 8)) + nPaddingColoured;
		}
		if ((obj_BMP.fnreturnBitamapwidth() % 8) != 0)
		{
			nByteBlackAndWhite = obj_BMP.fnreturnBitamapwidth() / 8;
		}
		else {
			nByteBlackAndWhite = obj_BMP.fnreturnBitamapwidth() / 8 + 1;
		}
		if ((nByteBlackAndWhite % 4) != 0)
		{
			nPaddingBlackAndWhite = 4 - (nByteBlackAndWhite % 4);
		}
		else {
			nPaddingBlackAndWhite = 0;
		}
		nLineLengthBlackAndWhite = nByteBlackAndWhite + nPaddingBlackAndWhite;
		DWORD bsizeofBMP = pBMPstructure->fngetSizeBMP();
		bsizeofBMP -= obj_BMP.fnreturnOffsetpixelarray();
		int nSectors = (bsizeofBMP-obj_BMP.fnreturnOffsetpixelarray()) / nLineLengthColoured;
		int nFlagHeader = 1,nFlagPixelArray=1;
		if (obj_file_to_read.fnCreate(argv[1], GENERIC_READ, OPEN_EXISTING) == FALSE)
		{
			dwErrCode = GetLastError();
			_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		if (obj_file_to_write.fnCreate(argv[2], GENERIC_WRITE, CREATE_ALWAYS) == FALSE)
		{
			dwErrCode = GetLastError();
			_tprintf(_T("\n\tThe error message:-%ws"), obj_error_handler.fngeterrordescription(dwErrCode));
			_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		while (nSectors)
		{
			if (nFlagHeader == 1)
			{
				if (obj_file_to_write.fnWrite(bReadBuffer, 62) == FALSE)//To write HEADERS to destination file
				{
					obj_file_to_write.fnClose();
					dwErrCode = GetLastError();
					_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
					return EXIT_FAILURE;
				}
				--nFlagHeader;
			}
			BYTE bNewReadBuffer[4096] = { 0 };
			if (nFlagPixelArray == 1)
			{
				DWORD dwptr = SetFilePointer(obj_file_to_read.fnGetHandle(), obj_BMP.fnreturnOffsetpixelarray(), NULL, FILE_BEGIN);
				if (dwptr == INVALID_SET_FILE_POINTER)
				{
					dwErrCode = GetLastError();
					_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
					return EXIT_FAILURE;
				}
				--nFlagPixelArray;
			}
			if (obj_file_to_read.fnRead(bNewReadBuffer, nLineLengthColoured) == FALSE)
			{
				obj_file_to_read.fnClose();
				obj_file_to_write.fnClose();
				dwErrCode = GetLastError();
				_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}
			
			BYTE bMonoBuffer[128] = { 0 };
			int nMonoBytes = ((nLineLengthColoured - nPaddingColoured) / 3 ) / (nLineLengthBlackAndWhite - nPaddingBlackAndWhite);//3 is BGR values 
			int nMonoAdditional= ((nLineLengthColoured - nPaddingColoured) / 3) % (nLineLengthBlackAndWhite - nPaddingBlackAndWhite);
			int nIteratorbNewReadBuffer = 0;
			while (nMonoBytes)//nMonoBytes specifies how many times will the bMonoBuffer will be filled
			{
				for (int i = 0; i < (nLineLengthBlackAndWhite - nPaddingBlackAndWhite); i++)
				{
					bMonoBuffer[i] = (bNewReadBuffer[nIteratorbNewReadBuffer] + bNewReadBuffer[nIteratorbNewReadBuffer + 1] + bNewReadBuffer[nIteratorbNewReadBuffer + 2])/3;
					nIteratorbNewReadBuffer += 3;
				}
				if (nPaddingBlackAndWhite != 0)
				{
					for (int i = (nLineLengthBlackAndWhite - nPaddingBlackAndWhite); i < nLineLengthBlackAndWhite; i++)
					{
						bMonoBuffer[i] = 00;
					}
				}
				if (obj_file_to_write.fnWrite(bMonoBuffer, nLineLengthBlackAndWhite) == FALSE)
				{
					obj_file_to_read.fnClose();
					obj_file_to_write.fnClose();
					dwErrCode = GetLastError();
					_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
					_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
					return EXIT_FAILURE;
				}
				nMonoBytes--;
			}
			if (nMonoAdditional != 0)
			{
				for (int i = 0; i < nMonoAdditional; i++)
				{
					bMonoBuffer[i] = ( bNewReadBuffer[nIteratorbNewReadBuffer] + bNewReadBuffer[nIteratorbNewReadBuffer + 1] + bNewReadBuffer[nIteratorbNewReadBuffer + 2]) / 3;
				}
				nMonoAdditional--;
			}
			nSectors--;
		}
		return 0;
	}
}