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
	char chMagiccharacter[] = ".bmp";
	obj_cmdline.fnCreateVector("-h1");//Option -h1 pushed to a private attribute (i.e) Vect vector
	obj_cmdline.fnCreateVector("-h2");//Option -h2 puched to Vect vector of CCmdLine class
	obj_cmdline.fnCreateVector("-i");//Option -i pushed to Vect vector of CCmdLine class
	obj_cmdline.fnCreateVector("-p");//Option -p pushed to Vect vector of CCmdLine class
	obj_cmdline.fnCreateVector("-o");//Option -o pushed to Vect vector of CCmdLine class 
	obj_cmdline.fnCreateVector("-bw");//Option -bw pushed to Vect bector of CCmdLine class
	if (obj_cmdline.fnCheckVector(argv[1]) == FALSE)
	{
		return EXIT_FAILURE;
	}
	if (obj_cmdline.fnCheckFILE(argv[2], chMagiccharacter) == FALSE)
	{
		return EXIT_FAILURE;
	}
	if ((obj_cmdline.fnGetCurrentOption() != "-o") || (obj_cmdline.fnGetCurrentOption() != "-bw"))
	{
		return EXIT_FAILURE;
	}
	CBMP obj_BMP;//object to BMP.cpp
	CFile obj_file_to_read, obj_file_to_write;//object to FILE.cpp with read and write conditions
	CError obj_error_handler;//object to Error.cpp
	DWORD dwErrCode;//Used for storing last error code
	BYTE bReadBuffer[nBUFFERSIZE] = { 0 };
	BMPstructure *pBMPstructure = new BMPstructure;//Creating a new BMPstructure pointer
	obj_BMP.fnsetStructurepointer(pBMPstructure);//Setting the created pBMPstructure to BMP.cpp so that can be used to get the values stored there
	if (obj_file_to_read.fnCreate(argv[2], GENERIC_READ, OPEN_EXISTING) == FALSE)//Handle is created to source file in GENERIC_READ mode
	{
		_tprintf(_T("\n\tCheck for source image existence."));
		dwErrCode = GetLastError();//Retriving the last error code
		_tprintf(_T("\n\tError message:%s"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
		_tprintf(_T("\n\tError code:%d"), obj_error_handler.fngetErrCode());//Retriving error code
		return EXIT_FAILURE;
	}
	if (obj_file_to_read.fnRead(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)//Reading data of size specified by m_knSECTORSIZE into bReadBuffer
	{
		dwErrCode = GetLastError();//Retriving the last error code
		_tprintf(_T("\n\tError message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
		_tprintf(_T("\n\tError code %d"), obj_error_handler.fngetErrCode());//Retriving error code
		return EXIT_FAILURE;
	}
	obj_file_to_read.fnClose();//Closing the handle which was opened for reading the BMP file into bReadBuffer
	INT nReadOffset = 0;//To copy particular bytes from buffer to BMPstructure.h's parameters
	memcpy(&(pBMPstructure->m_wFiletype), bReadBuffer + nReadOffset, 2); nReadOffset += 2;//Copying memory to m_wFiletype a parameter in BMPstructure.h
	memcpy(&(pBMPstructure->m_dwSizeBMP), bReadBuffer + nReadOffset, 4); nReadOffset += 4;//Copying memory to m_dwSizeBMP a parameter in BMPstructure.h
	memcpy(&(pBMPstructure->m_wReserved1), bReadBuffer + nReadOffset, 2); nReadOffset += 2;//Copying memory to m_wReserved1 a parameter in BMPstructure.h
	memcpy(&(pBMPstructure->m_wReserved2), bReadBuffer + nReadOffset, 2); nReadOffset += 2;//Copying memory to m_wReserved2 a parameter in BMPstructure.h
	memcpy(&(pBMPstructure->m_dwOffsetpixelarray), bReadBuffer + nReadOffset, 4); nReadOffset += 4;//Copying memory to m_dwOffsetpixelarray a parameter in BMPstructure.h
	memcpy(&(pBMPstructure->m_dwSizebitmapinfoheader), bReadBuffer + nReadOffset, 4); nReadOffset += 4;//Copying memory to m_dwSizebitmapinfoheader a parameter in BMPstructure.h
	memcpy(&(pBMPstructure->m_nBitmapwidth), bReadBuffer + nReadOffset, 4); nReadOffset += 4;//Copying memory to m_nBitmapwidth a parameter in BMPstructure.h
	memcpy(&(pBMPstructure->m_nBitmapheight), bReadBuffer + nReadOffset, 4); nReadOffset += 4;//Copying memory to m_nBitmapheight a parameter in BMPstructure.h
	memcpy(&(pBMPstructure->m_wColorplanes), bReadBuffer + nReadOffset, 2); nReadOffset += 2;//Copying memory to m_wColorplanes a parameter in BMPstructure.h
	memcpy(&(pBMPstructure->m_wColordepth), bReadBuffer + nReadOffset, 2); nReadOffset += 2;//Copying memory to m_wColordepth a parameter in BMPstructure.h
	memcpy(&(pBMPstructure->m_dwCompressionmethod), bReadBuffer + nReadOffset, 4); nReadOffset += 4;//Copying memory to m_dwCompressionmethod a parameter in BMPstructure.h
	memcpy(&(pBMPstructure->m_dwRawimagesize), bReadBuffer + nReadOffset, 4); nReadOffset += 4;//Copying memory to m_dwRawimagesize a parameter in BMPstructure.h
	memcpy(&(pBMPstructure->m_dwHorizontalresolution), bReadBuffer + nReadOffset, 4); nReadOffset += 4;//Copying memory to m_dwHorizontalresolution a parameter in BMPstructure.h
	memcpy(&(pBMPstructure->m_dwVerticalresolution), bReadBuffer + nReadOffset, 4); nReadOffset += 4;//Copying memory to m_dwVerticalresolution a parameter in BMPstructure.h
	memcpy(&(pBMPstructure->m_dwColorpallete), bReadBuffer + nReadOffset, 4); nReadOffset += 4;//Copying memory to m_dwSizeBMP a parameter in BMPstructure.h
	memcpy(&(pBMPstructure->m_dwImportantcolors), bReadBuffer + nReadOffset, 4); nReadOffset += 4;//Copying memory to m_dwImportantcolors a parameter in BMPstructure.h
	int nChoice;//variable to be used to configure switch statement
	if (obj_cmdline.fnGetCurrentOption() == "-h1") { nChoice = 1; }//1 if -h1 i.e Bitmap info header
	if (obj_cmdline.fnGetCurrentOption() == "-h2") { nChoice = 2; }//2 if -h2 i.e DIB header
	if (obj_cmdline.fnGetCurrentOption() == "-i")  { nChoice = 3; }//3 if -i i.e general information
	if (obj_cmdline.fnGetCurrentOption() == "-p")  { nChoice = 4; }//4 if -p i.e pixel array
	if (obj_cmdline.fnGetCurrentOption() == "-o")  { nChoice = 5; }//5 if -o i.e original image copy
	if (obj_cmdline.fnGetCurrentOption() == "-bw") { nChoice = 6; }//6 if -bw i.e black and white image copy
	switch (nChoice)
	{
	case 1:
	{
		cout << hex << obj_BMP.fnreturnFiletype() << " " << obj_BMP.fnreturnSizeBMP() << " " << obj_BMP.fnreturnReserved1() << " " << obj_BMP.fnreturnReserved2() << " " << obj_BMP.fnreturnOffsetpixelarray();
		break;
	}
	case 2:
	{
		cout << obj_BMP.fnreturnSizebitmapinfoheader() << " " << obj_BMP.fnreturnBitamapwidth() << " " << obj_BMP.fnreturnBitmapheight() << " " << obj_BMP.fnreturnColorplanes() << endl;
		cout << obj_BMP.fnreturnColordepth() << " " << obj_BMP.fnreturnCompressionmethod() << " " << obj_BMP.fnreturnRawimagesize() << endl;
		cout << obj_BMP.fnreturnHorizontalresolution() << " " << obj_BMP.fnreturnVerticalresolution() << " " << obj_BMP.fnreturnColorplanes() << " " << obj_BMP.fnreturnImportantcolors() << endl;
		break;
	}
	case 3:
	{
		if (obj_BMP.fncheckFiletype() == TRUE)//Checking if the file is BMP image file or not
		{
			_tprintf(_T("---------------------------------------------------------------------------------------------\n"));
			_tprintf(_T("\n\n\t\t\t\t\tValid BMP image file.\n\n"));
			_tprintf(_T("---------------------------------------------------------------------------------------------\n"));
			_tprintf(_T("\t\t\t\tInformation of BMP image file\n\n"));
			_tprintf(_T("\tSize of BMP file(in bytes) :\t\t\t%u\n"), obj_BMP.fnreturnSizeBMP());//Returning 
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
		break;
	}
	case 4:
	{
		DWORD bsizeofBMP = pBMPstructure->fngetSizeBMP();
		bsizeofBMP -= obj_BMP.fnreturnOffsetpixelarray();
		int nSectors = bsizeofBMP / CFile::m_knSECTORSIZE;
		int nAdditional = bsizeofBMP % CFile::m_knSECTORSIZE;
		int nFlagPixelArray = 1;
		if (obj_file_to_read.fnCreate(argv[2], GENERIC_READ, OPEN_EXISTING) == FALSE)
		{
			dwErrCode = GetLastError();//Retriving the last error code
			_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
			_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		if (obj_file_to_write.fnCreate(argv[3], GENERIC_WRITE, CREATE_ALWAYS) == FALSE)
		{
			dwErrCode = GetLastError();
			_tprintf(_T("\n\tThe error message:-%ws"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
			_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		while (nSectors)
		{
			if (nFlagPixelArray == 1)
			{
				DWORD dwptr = SetFilePointer(obj_file_to_read.fnGetHandle(), obj_BMP.fnreturnOffsetpixelarray(), NULL, FILE_BEGIN);
				if (dwptr == INVALID_SET_FILE_POINTER)
				{
					dwErrCode = GetLastError();//Retriving the last error code
					_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
					_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
					return EXIT_FAILURE;
				}
			}
			if (obj_file_to_read.fnRead(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)
			{
				obj_file_to_read.fnClose();
				obj_file_to_write.fnClose();
				dwErrCode = GetLastError();//Retriving the last error code
				_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
				_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}
			if (obj_file_to_write.fnWrite(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)
			{
				obj_file_to_read.fnClose();
				obj_file_to_write.fnClose();
				dwErrCode = GetLastError();//Retriving the last error code
				_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
				_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}
			--nFlagPixelArray;


			nSectors--;
		}
		if (obj_file_to_read.fnRead(bReadBuffer, nAdditional) == FALSE)
		{
			dwErrCode = GetLastError();//Retriving the last error code
			obj_file_to_read.fnClose();//Closing the handle opened for reading
			obj_file_to_write.fnClose();//closing the handle which was opened for writing
			_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
			_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		if (obj_file_to_write.fnWrite(bReadBuffer, nAdditional) == FALSE)
		{
			dwErrCode = GetLastError();//Retriving the last error code
			obj_file_to_read.fnClose();//Closing the handle opened for reading
			obj_file_to_write.fnClose();//closing the handle which was opened for writing
			_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
			_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}

		break;
	}
	case 5:
	{
		DWORD bsizeofBMP = pBMPstructure->fngetSizeBMP();//Getting the size of BMP image 
		int nSectors = bsizeofBMP / CFile::m_knSECTORSIZE;//Calculating how many sectors does the image contain for size eqivalent to m_knSECTORSIZE
		int nAdditional = bsizeofBMP % CFile::m_knSECTORSIZE;//Calculating how many remaining bytes left after calculating sectors
		if (obj_file_to_read.fnCreate(argv[2], GENERIC_READ, OPEN_EXISTING) == FALSE)//Creating a handle to source file
		{
			dwErrCode = GetLastError();//Retriving the last error code
			_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
			_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		if (obj_file_to_write.fnCreate(argv[3], GENERIC_WRITE, CREATE_ALWAYS) == FALSE)//Creating a handle to destination file
		{
			dwErrCode = GetLastError();//Retriving the last error code
			_tprintf(_T("\n\tThe error message:-%ws"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message 
			_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		while (nSectors)
		{
			if (obj_file_to_read.fnRead(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)//Reading m_knSECTORSIZE number of bytes to bReadBuffer 
			{
				obj_file_to_read.fnClose();//Closing handle which was opened for reading via source file
				obj_file_to_write.fnClose();//closing handle which was opened for writing to destination file
				dwErrCode = GetLastError();//Retriving the last error code
				_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
				_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}
			if (obj_file_to_write.fnWrite(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)//Writing the bytes from bReadBuffer to destination by use of handle according to m_knSECTORSIZE
			{
				obj_file_to_read.fnClose();//Closing handle which was opened for reading via source file
				obj_file_to_write.fnClose();//closing handle which was opened for writing to destination file
				dwErrCode = GetLastError();//Retriving the last error code
				_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
				_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}

			nSectors--;
		}
		if (obj_file_to_read.fnRead(bReadBuffer, nAdditional) == FALSE)//Reading the reamining bytes from source file 
		{
			obj_file_to_read.fnClose();//Closing handle which was opened for reading via source file
			obj_file_to_write.fnClose();//closing handle which was opened for writing to destination file
			dwErrCode = GetLastError();//Retriving the last error code
			_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
			_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		if (obj_file_to_write.fnWrite(bReadBuffer, nAdditional) == FALSE)//Writing the readed remaining bytes to destination file
		{
			obj_file_to_read.fnClose();//Closing handle which was opened for reading via source file
			obj_file_to_write.fnClose();//closing handle which was opened for writing to destination file
			dwErrCode = GetLastError();//Retriving the last error code
			_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
			_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		break;
	}
	case 6:
	{
		//Creating Bitamp file header and DIB header for black and white image
		int nBitmapImageWidth = pBMPstructure->fngetBitmapwidth();
		int nRowSize = ((nBitmapImageWidth + 31) / 32) * 4;
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
		if (obj_BMP.fnreturnColordepth() == 24)//Checking if the color depth(bits per pixel)
		{
			if (((obj_BMP.fnreturnBitamapwidth() * (obj_BMP.fnreturnColordepth() / 8)) % 4) != 0)//Calculating padding for coloured image i.e our source image 
			{
				nPaddingColoured = 4 - ((obj_BMP.fnreturnBitamapwidth() * (obj_BMP.fnreturnColordepth()) / 8) % 4);
			}
			else
			{
				nPaddingColoured = 0;
			}
			nLineLengthColoured = (obj_BMP.fnreturnBitamapwidth() * (obj_BMP.fnreturnColordepth() / 8)) + nPaddingColoured;//length of 1 line including padding bytes
		}
		if ((obj_BMP.fnreturnBitamapwidth() % 8) != 0)//Calculating the bytes for black and white image
		{
			nByteBlackAndWhite = obj_BMP.fnreturnBitamapwidth() / 8;
		}
		else {
			nByteBlackAndWhite = obj_BMP.fnreturnBitamapwidth() / 8 + 1;
		}
		if ((nByteBlackAndWhite % 4) != 0)//Calculating padding have to be done in converted black and white image
		{
			nPaddingBlackAndWhite = 4 - (nByteBlackAndWhite % 4);
		}
		else {
			nPaddingBlackAndWhite = 0;
		}
		nLineLengthBlackAndWhite = nByteBlackAndWhite + nPaddingBlackAndWhite;//Length of 1 line have to be there in black and white image
		DWORD bsizeofBMP = pBMPstructure->fngetSizeBMP();
		bsizeofBMP -= obj_BMP.fnreturnOffsetpixelarray();
		int nSectors = (bsizeofBMP - obj_BMP.fnreturnOffsetpixelarray()) / nLineLengthColoured;
		int nFlagHeader = 1, nFlagPixelArray = 1;
		if (obj_file_to_read.fnCreate(argv[2], GENERIC_READ, OPEN_EXISTING) == FALSE)//Creating a handle to Source image file
		{
			dwErrCode = GetLastError();//Retriving the last error code
			_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
			_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		if (obj_file_to_write.fnCreate(argv[3], GENERIC_WRITE, CREATE_ALWAYS) == FALSE)//Craeting a handle to destination image file
		{
			dwErrCode = GetLastError();//Retriving the last error code
			_tprintf(_T("\n\tThe error message:-%ws"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
			_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
			_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
			return EXIT_FAILURE;
		}
		while (nSectors)
		{
			if (nFlagHeader == 1)//So that pointer goes only one times inside this very code
			{
				if (obj_file_to_write.fnWrite(bReadBuffer, 62) == FALSE)//To write HEADERS to destination file
				{
					obj_file_to_write.fnClose();//Closing the handle opened for writing to the file
					dwErrCode = GetLastError();//Retriving the last error code
					_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
					_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
					return EXIT_FAILURE;
				}
				--nFlagHeader;
			}
			BYTE bNewReadBuffer[4096] = { 0 };//Creating a new array to load one line of source file
			if (nFlagPixelArray == 1)//For first iteration need to set the file pointer to after both headers so that it is not overwritten
			{
				DWORD dwptr = SetFilePointer(obj_file_to_read.fnGetHandle(), obj_BMP.fnreturnOffsetpixelarray(), NULL, FILE_BEGIN);//SetFilePointer WinAPI
				if (dwptr == INVALID_SET_FILE_POINTER)//Check if it is pointing to the desired or giving some garbage value
				{
					dwErrCode = GetLastError();//Retriving the last error code
					_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
					_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
					return EXIT_FAILURE;
				}
				--nFlagPixelArray;//Decrementing so that it will no enter in this part of code
			}
			if (obj_file_to_read.fnRead(bNewReadBuffer, nLineLengthColoured) == FALSE)
			{
				obj_file_to_read.fnClose();
				obj_file_to_write.fnClose();
				dwErrCode = GetLastError();//Retriving the last error code
				_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
				_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}
			BYTE bMonoBuffer[128] = { 0 };//It is the buffer which is made for storing single line of black and white image
			int nMonoBytes = ((nLineLengthColoured - nPaddingColoured) / 3) / (nLineLengthBlackAndWhite - nPaddingBlackAndWhite);//3 is BGR values and calculating rthe sectors
			int nMonoAdditional = ((nLineLengthColoured - nPaddingColoured) / 3) % (nLineLengthBlackAndWhite - nPaddingBlackAndWhite);//Calculating the additional bytes which is remaining after calculating the sectors
			int nIteratorbNewReadBuffer = 0;
			while (nMonoBytes)//nMonoBytes specifies how many times will the bMonoBuffer will be filled
			{
				for (int i = 0; i < (nLineLengthBlackAndWhite - nPaddingBlackAndWhite); i++)//Loop started for the amount of 1 line which is to be feeded inside the monochrome image
				{
					bMonoBuffer[i] = (bNewReadBuffer[nIteratorbNewReadBuffer] + bNewReadBuffer[nIteratorbNewReadBuffer + 1] + bNewReadBuffer[nIteratorbNewReadBuffer + 2]) / 3;//Algorithm for conversion from bgr value to monochrome/black ad white i.e the average of all the three value
					nIteratorbNewReadBuffer += 3;//Incrementing the iterator for bNewReadBuffer which is containg one single line of coloured BMP
				}
				if (nPaddingBlackAndWhite != 0)//if padding of black and whiote is not zero
				{
					for (int i = (nLineLengthBlackAndWhite - nPaddingBlackAndWhite); i < nLineLengthBlackAndWhite; i++)//from the position where data of black and white image ends   
					{
						bMonoBuffer[i] = 00;
					}
				}
				if (obj_file_to_write.fnWrite(bMonoBuffer, nLineLengthBlackAndWhite) == FALSE)
				{
					obj_file_to_read.fnClose();
					obj_file_to_write.fnClose();
					dwErrCode = GetLastError();//Retriving the last error code
					_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
					_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
					_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
					return EXIT_FAILURE;
				}
				nMonoBytes--;
			}
			if (nMonoAdditional != 0)//The remaining bytes
			{//Problem here is that the last remaining bytes will be of certain bytes and will be copied to destination but when next iteration starts it will continue 
				//to convert the whole line for monobytes instead it should be the new bytes have to be readed minus the additional one already readed..
				for (int i = 0; i < nMonoAdditional; i++)
				{
					bMonoBuffer[i] = (bNewReadBuffer[nIteratorbNewReadBuffer] + bNewReadBuffer[nIteratorbNewReadBuffer + 1] + bNewReadBuffer[nIteratorbNewReadBuffer + 2]) / 3;
				}
				nMonoAdditional--;
			}
			nSectors--;
		}
		break;
	}
	}
}
	
	
	
	
