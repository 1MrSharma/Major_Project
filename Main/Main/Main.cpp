#include "pch.h"
#include <iostream>
#include<tchar.h>
#include<tchar.h>
#include<cstdio>
#include<vector>
#include<algorithm>
#include"BMP.h"
#include"File.h"
#include"Error.h"
#include"Cmdline.h"
#include<cmath>

void copyToStructure(BMPstructure*, BYTE[]);
float GammaExpansion(float);
int hexadecimalToDecimal(BYTE[]);
float LinearIntesityValue(float, float, float);
//void fillBuffer(float, BYTE*,int);

using namespace std;

const int nBUFFERSIZE = 1024;
const int nBUFFERSIZEbMonoReadBuffer = 62;
//const char* const chmagicCharacter = ".bmp$";
const char chmagicCharacter[6] = ".bmp$";
const int nOffsetPixelArrayMono = 0x3E;
const int nSizeBitmapInfoHeaderMono = 0x28;
const int nColorDepthMono = 1;
const int nColorTableWhiteMono = 0x00;
const int nColorTableBlackMono = 0xff;
const int nColorDepth24 = 24;
const int nPixelColorValue = 3;//BGR
const int nMaxArgumentSupported = 3;
const int nMultiple4Check = 4;
const int nMono8bpp = 8;
const float fThreshold = 0.5;
const int nWhite = 1;
const int nBlack = 0;
const int nTotalValuePixel = 765;//255*3



int main(int argc, TCHAR *argv[])
{
	if (argc >= nMaxArgumentSupported)
	{

		//Command line operation starts

		CCmdLine objCmdline;

		//Adding options starts
		objCmdline.Addoptions("-h1");
		objCmdline.Addoptions("-H1");
		objCmdline.Addoptions("-h2");
		objCmdline.Addoptions("-H2");
		objCmdline.Addoptions("-i");
		objCmdline.Addoptions("-I");
		objCmdline.Addoptions("-p");
		objCmdline.Addoptions("-P");
		objCmdline.Addoptions("-o");
		objCmdline.Addoptions("-O");
		objCmdline.Addoptions("-bw");
		objCmdline.Addoptions("-BW");
		//Adding options ends

		if (objCmdline.Searchoptionslist(argv[1]) == FALSE)//Checking whether first argument is from the available options
		{
			return EXIT_FAILURE;
		}
		if (objCmdline.Checkextension(argv[2], chmagicCharacter) == FALSE)//Checking whether the second argument's extension matches the chmagicCharacter
		{
			return EXIT_FAILURE;
		}

		//Command line operation ends


		//Declarations starts

		CBMP objBmp;
		CFile objFileToRead, objFileToWrite;
		CError objErrorHandler;
		DWORD dwErrCode;//Used for storing last error code
		BYTE bReadBuffer[nBUFFERSIZE] = { 0 };
		BMPstructure *pBMPstructure = new BMPstructure;//Creating a new BMPstructure pointer
		int nChoice;//variable to be used to configure switch statement


		//Declarations ends

		objBmp.fnsetStructurepointer(pBMPstructure);//Setting the created pBMPstructure to BMP.cpp so that can be used to get the values stored there

		if (objFileToRead.fnCreate(argv[2], GENERIC_READ, OPEN_EXISTING) == FALSE)//Handle is created to source file in GENERIC_READ mode
		{
			_tprintf(_T("\n\tCheck for source image existence."));
			dwErrCode = GetLastError();//Retriving the last error code
			_tprintf(_T("\n\tError message:%s"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
			_tprintf(_T("\n\tError code:%d"), objErrorHandler.fngetErrCode());//Retriving error code
			return EXIT_FAILURE;
		}

		if (objFileToRead.fnRead(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)//Reading data of size specified by m_knSECTORSIZE into bReadBuffer
		{
			dwErrCode = GetLastError();//Retriving the last error code
			_tprintf(_T("\n\tError message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
			_tprintf(_T("\n\tError code %d"), objErrorHandler.fngetErrCode());//Retriving error code
			return EXIT_FAILURE;
		}
		objFileToRead.fnClose();


		copyToStructure(pBMPstructure, bReadBuffer);

		if (objCmdline.GetCurrentOption() == "-h1") { nChoice = 1; }//1 if -h1 i.e Bitmap info header
		if (objCmdline.GetCurrentOption() == "-H1") { nChoice = 1; }//1 if -H1 i.e Bitmap info header
		if (objCmdline.GetCurrentOption() == "-h2") { nChoice = 2; }//2 if -h2 i.e DIB header
		if (objCmdline.GetCurrentOption() == "-H2") { nChoice = 2; }//2 if -H2 i.e DIB header
		if (objCmdline.GetCurrentOption() == "-i") { nChoice = 3; }//3 if -i i.e general information
		if (objCmdline.GetCurrentOption() == "-I") { nChoice = 3; }//3 if -I i.e general information
		if (objCmdline.GetCurrentOption() == "-p") { nChoice = 4; }//4 if -p i.e pixel array
		if (objCmdline.GetCurrentOption() == "-P") { nChoice = 4; }//4 if -P i.e pixel array
		if (objCmdline.GetCurrentOption() == "-o") { nChoice = 5; }//5 if -o i.e original image copy
		if (objCmdline.GetCurrentOption() == "-O") { nChoice = 5; }//5 if -O i.e original image copy
		if (objCmdline.GetCurrentOption() == "-bw") { nChoice = 6; }//6 if -bw i.e black and white image copy
		if (objCmdline.GetCurrentOption() == "-BW") { nChoice = 6; }//6 if -BW i.e black and white image copy

		DWORD bsizeofBMP = pBMPstructure->fngetSizeBMP();

		int nSectors = bsizeofBMP / CFile::m_knSECTORSIZE;
		int nAdditional = bsizeofBMP % CFile::m_knSECTORSIZE;
		switch (nChoice)
		{
		case 1://Bitmap info header
		{
			cout << hex << objBmp.fnreturnFiletype() << " " 
				<< objBmp.fnreturnSizeBMP() << " " << objBmp.fnreturnReserved1() 
				<< " " << objBmp.fnreturnReserved2() << " " << objBmp.fnreturnOffsetpixelarray();
			break;
		}
		case 2:// DIB header
		{
			cout << objBmp.fnreturnSizebitmapinfoheader() << " " << objBmp.fnreturnBitamapwidth() 
				<< " " << objBmp.fnreturnBitmapheight() << " " << objBmp.fnreturnColorplanes() << endl;
			cout << objBmp.fnreturnColordepth() << " " << objBmp.fnreturnCompressionmethod() 
				<< " " << objBmp.fnreturnRawimagesize() << endl;
			cout << objBmp.fnreturnHorizontalresolution() << " " << objBmp.fnreturnVerticalresolution() 
				<< " " << objBmp.fnreturnColorplanes() << " " << objBmp.fnreturnImportantcolors() << endl;
			break;
		}
		case 3://general information
		{
			if (objBmp.fncheckFiletype() == TRUE)//Checking if the file is BMP image file or not
			{
				_tprintf(_T("---------------------------------------------------------------------------------------------\n"));
				_tprintf(_T("\n\n\t\t\t\t\tValid BMP image file.\n\n"));
				_tprintf(_T("---------------------------------------------------------------------------------------------\n"));
				_tprintf(_T("\t\t\t\tInformation of BMP image file\n\n"));
				_tprintf(_T("\tSize of BMP file(in bytes) :\t\t\t%u\n"), objBmp.fnreturnSizeBMP());//Returning 
				_tprintf(_T("\tOffset pixel array :\t\t\t%d\n"), objBmp.fnreturnOffsetpixelarray());
				_tprintf(_T("\tSize of Bitmap info header :\t\t\t%d\n"), objBmp.fnreturnSizebitmapinfoheader());
				_tprintf(_T("\tBitmap width in pixels :\t\t\t%d\n"), objBmp.fnreturnBitamapwidth());
				_tprintf(_T("\tBitmap height in pixels :\t\t\t%d\n"), objBmp.fnreturnBitmapheight());
				_tprintf(_T("\tColor planes :\t\t\t\t\t%d\n"), objBmp.fnreturnColorplanes());
				_tprintf(_T("\tColor depth(bits per pixel) :\t\t\t%d\n"), objBmp.fnreturnColordepth());
				_tprintf(_T("\tCompression method\n"));
				if (objBmp.fnreturnCompressionmethod() == 0)
				{
					_tprintf(_T("\t\tValue :\t\t\t\t\t0\n\t\tIdentified by :\t\t\t\tBI_RGB\n\t\tCompression :\t\t\t\tNone\n\t\tComments :\t\t\t\tMost commonly used.\n"));
				}
				if (objBmp.fnreturnCompressionmethod() == 1)
				{
					_tprintf(_T("\t\tValue :\t\t\t\t\t1\n\t\tIdentified by :\t\t\t\tBI_RLE8\n\t\tCompression :\t\t\t\tRLE 8-bit/pixel\n\t\tComments :\t\t\t\tOnly with 8-bit/pixel bitmaps.\n"));
				}
				if (objBmp.fnreturnCompressionmethod() == 2)
				{
					_tprintf(_T("\t\tValue :\t\t\t\t\t2\n\t\tIdentified by :\t\t\t\tBI_RLE4\n\t\tCompression :\t\t\t\tRLE 4-bit/pixel\n\t\tComments :\t\t\t\tCan be used only with 4-bit/pixel bitmaps.\n"));
				}
				if (objBmp.fnreturnCompressionmethod() == 3)
				{
					_tprintf(_T("\t\tValue :\t\t\t\t\t3\n\t\tIdentified by :\t\t\t\tBI_BITFIELDS\n\t\tCompression :\t\t\t\tOS22XBITMAPHEADER : Huffman 1D\n\t\tComments :\t\t\t\tOnly for OS/2 2.x or later.\n"));
				}
				if (objBmp.fnreturnCompressionmethod() == 4)
				{
					_tprintf(_T("\t\tValue :\t\t\t\t\t4\n\t\tIdentified by :\t\t\t\tBI_JPEG\n\t\tCompression :\t\t\t\tOS22XBITMAPHEADER : RLE-24\n\t\tComments :\t\t\t\tOnly for OS/2 2.x or later & for Windows NT 4.0 and 95 or later (i.e) 'BITMAPV4INFOHEADER+' JPEG image for printing.\n"));
				}
				if (objBmp.fnreturnCompressionmethod() == 5)
				{
					_tprintf(_T("\t\tValue :\t\t\t\t\t5\n\t\tIdentified by :\t\t\t\tBI_PNG\n\t\tCompression :\t\t\t\tNone\n\t\tComments :\t\t\t\tFor Windows NT 4.0 and 95 or later (i.e) 'BITMAPV4INFOHEADER+' PNG image for printing\n"));
				}
				if (objBmp.fnreturnCompressionmethod() == 6)
				{
					_tprintf(_T("\t\tValue :\t\t\t\t\t6\n\t\tIdentified by :\t\t\t\tBI_ALPHABITFIELDS\n\t\tCompression :\t\t\t\tRGBA bit field masks\n\t\tComments :\t\t\t\tOnly for Windows CE 5.0 with .NET 4.0 or later\n"));
				}
				if (objBmp.fnreturnCompressionmethod() == 11)
				{
					_tprintf(_T("\t\tValue :\t\t\t\t\t11\n\t\tIdentified by :\t\t\t\tBI_CMYK\n\t\tCompression :\t\t\t\tNone\n\t\tComments :\t\t\t\tOnly for Windows Metafile CMYK\n"));
				}
				if (objBmp.fnreturnCompressionmethod() == 12)
				{
					_tprintf(_T("\t\tValue :\t\t\t\t\t12\n\t\tIdentified by :\t\t\t\tBI_CMYKRLE8\n\t\tCompression :\t\t\t\tRLE-8\n\t\tComments :\t\t\t\tOnly Windows Metafile CMYK\n"));
				}
				if (objBmp.fnreturnCompressionmethod() == 13)
				{
					_tprintf(_T("\tValue :\t\t\t\t\t13\tIdentified by :\t\t\t\tBI_CMYKRLE4\tCompression :\t\t\t\tRLE-4\tComments :\t\t\t\tonly Windows Metafile CMYK\n"));
				}
				_tprintf(_T("\tSize of the raw bitmap data  :\t\t\t%d\n"), objBmp.fnreturnRawimagesize());
				_tprintf(_T("\tHorizontal resolution(pixel per meter) :\t%d\n"), objBmp.fnreturnHorizontalresolution());
				_tprintf(_T("\tVertical resolution(pixel per meter) :\t\t%d\n"), objBmp.fnreturnVerticalresolution());
				_tprintf(_T("\tNumber of colors in color palette :\t\t%d\n"), objBmp.fnreturnColorpallete());
				_tprintf(_T("\tImportant colors used :\t\t\t\t%d"), objBmp.fnreturnImportantcolors());
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
		case 4://pixel array
		{

			bsizeofBMP -= objBmp.fnreturnOffsetpixelarray();

			if (objFileToRead.fnCreate(argv[2], GENERIC_READ, OPEN_EXISTING) == FALSE)
			{
				dwErrCode = GetLastError();//Retriving the last error code
				_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
				_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());//Retriving error code
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}
			DWORD dwptr = SetFilePointer(objFileToRead.fnGetHandle(), objBmp.fnreturnOffsetpixelarray(), NULL, FILE_BEGIN);
			if (dwptr == INVALID_SET_FILE_POINTER)
			{
				dwErrCode = GetLastError();//Retriving the last error code
				_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
				_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());//Retriving error code
				return EXIT_FAILURE;
			}
			char userChoice;//Pixel array
			cout << "Do you want to see complete pixel array ? [Y/N] " << endl;
			cin >> userChoice;
			if (userChoice == 'N' || userChoice == 'n')
			{
				return 0;
			}
			while (nSectors)
			{
				if (objFileToRead.fnRead(bReadBuffer, nBUFFERSIZE) == FALSE)
				{
					objFileToRead.fnClose();
					objFileToWrite.fnClose();
					dwErrCode = GetLastError();//Retriving the last error code
					_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
					_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());//Retriving error code
					_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
					return EXIT_FAILURE;
				}
				for (int i = 0; i < 1024; i++)
				{
					cout << hex << (int)bReadBuffer[i] << " " << endl;
				}
				nSectors--;
			}
			if (objFileToRead.fnRead(bReadBuffer, nAdditional) == FALSE)
			{
				objFileToRead.fnClose();
				objFileToWrite.fnClose();
				dwErrCode = GetLastError();//Retriving the last error code
				_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
				_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());//Retriving error code
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}
			for (int i = 0; i < nAdditional; i++)
			{
				cout << hex << (int)bReadBuffer[i] << " ";
			}
			break;
		}
		case 5://original image copy
		{

			if (objFileToRead.fnCreate(argv[2], GENERIC_READ, OPEN_EXISTING) == FALSE)//Creating a handle to source file
			{
				dwErrCode = GetLastError();//Retriving the last error code
				_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
				_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());//Retriving error code
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}
			if (objFileToWrite.fnCreate(argv[3], GENERIC_WRITE, CREATE_ALWAYS) == FALSE)//Creating a handle to destination file
			{
				dwErrCode = GetLastError();//Retriving the last error code
				_tprintf(_T("\n\tThe error message:-%ws"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message 
				_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());//Retriving error code
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}
			while (nSectors)
			{
				if (objFileToRead.fnRead(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)//Reading m_knSECTORSIZE number of bytes to bReadBuffer 
				{
					objFileToRead.fnClose();//Closing handle which was opened for reading via source file
					objFileToWrite.fnClose();//closing handle which was opened for writing to destination file
					dwErrCode = GetLastError();//Retriving the last error code
					_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
					_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());//Retriving error code
					_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
					return EXIT_FAILURE;
				}
				if (objFileToWrite.fnWrite(bReadBuffer, CFile::m_knSECTORSIZE) == FALSE)//Writing the bytes from bReadBuffer to destination by use of handle according to m_knSECTORSIZE
				{
					objFileToRead.fnClose();//Closing handle which was opened for reading via source file
					objFileToWrite.fnClose();//closing handle which was opened for writing to destination file
					dwErrCode = GetLastError();//Retriving the last error code
					_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
					_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());//Retriving error code
					_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
					return EXIT_FAILURE;
				}

				nSectors--;
			}
			if (objFileToRead.fnRead(bReadBuffer, nAdditional) == FALSE)//Reading the reamining bytes from source file 
			{
				objFileToRead.fnClose();//Closing handle which was opened for reading via source file
				objFileToWrite.fnClose();//closing handle which was opened for writing to destination file
				dwErrCode = GetLastError();//Retriving the last error code
				_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
				_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());//Retriving error code
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}
			if (objFileToWrite.fnWrite(bReadBuffer, nAdditional) == FALSE)//Writing the readed remaining bytes to destination file
			{
				objFileToRead.fnClose();//Closing handle which was opened for reading via source file
				objFileToWrite.fnClose();//closing handle which was opened for writing to destination file
				dwErrCode = GetLastError();//Retriving the last error code
				_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
				_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());//Retriving error code
				_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
				return EXIT_FAILURE;
			}
			break;
		}
		case 6://black and white image copy
		{
			BYTE bMonoReadBuffer[nBUFFERSIZEbMonoReadBuffer] = { 0 };
			//Creating header for black and white image
			int nBitmapImageWidth = objBmp.fnreturnBitamapwidth();
			DWORD dwBitmapHeight = objBmp.fnreturnBitmapheight();
			int nSizeRawBitmap = (((nBitmapImageWidth + 31) / 32) * 4) * dwBitmapHeight;
			int nSizeBMP = nSizeRawBitmap + nOffsetPixelArrayMono;
			WORD filetype = objBmp.fnreturnFiletype();
			//Bitmap file header starts
			memcpy(bMonoReadBuffer + 0, &filetype, 2);						//Magic characters of bmp (i.e) 0x42 0x4D
			memcpy(bMonoReadBuffer + 2, &nSizeBMP, 2);						//Size of BMP file in bytes
			bMonoReadBuffer[6] = objBmp.fnreturnReserved1();				//Reserved
			bMonoReadBuffer[8] = objBmp.fnreturnReserved2();				//Reserved
			bMonoReadBuffer[10] = nOffsetPixelArrayMono;					//Offset,(i.e) where the bitmap image data can be found
			//Bitmap file header ends
			//DIB Header starts
			bMonoReadBuffer[14] = nSizeBitmapInfoHeaderMono;				//Size of DIB header.
			memcpy(bMonoReadBuffer + 18, &nBitmapImageWidth, 4);			//The bitmap width in pixels.
			memcpy(bMonoReadBuffer + 22, &dwBitmapHeight, 4);				//The bitmap height in pixels.
			bMonoReadBuffer[26] = objBmp.fnreturnColorplanes();				//The number of color planes.
			bMonoReadBuffer[28] = nColorDepthMono;							//Number of bits per pixel, which is the color depth of the image.
			bMonoReadBuffer[30] = objBmp.fnreturnCompressionmethod();		//The compression method being used.
			memcpy(bMonoReadBuffer + 34, &nSizeRawBitmap, 4);				//The image size.
			bMonoReadBuffer[38] = objBmp.fnreturnHorizontalresolution();	//The horizontal resolution of the image.
			bMonoReadBuffer[42] = objBmp.fnreturnVerticalresolution();		//The vertical resolution of the image. 
			bMonoReadBuffer[46] = objBmp.fnreturnColorpallete();			//The number of colors in the color palette.
			bMonoReadBuffer[50] = objBmp.fnreturnImportantcolors();			//The number of important colors used.
			bMonoReadBuffer[54] = nColorTableWhiteMono;						//Color table begins.
			bMonoReadBuffer[55] = nColorTableWhiteMono;						//..
			bMonoReadBuffer[56] = nColorTableWhiteMono;						//..
			bMonoReadBuffer[57] = nColorTableWhiteMono;						//..
			bMonoReadBuffer[58] = nColorTableBlackMono;						//..
			bMonoReadBuffer[59] = nColorTableBlackMono;						//..
			bMonoReadBuffer[60] = nColorTableBlackMono;						//..
			bMonoReadBuffer[61] = nColorTableWhiteMono;						//Color table ends.
			//DIB Header ends

			//End of creating header for black and white

			//Calculating the linelength and padding bytes for required monochrome/black and white image
			int nByteBlackAndWhite, nPaddingBlackAndWhite;
			if (nBitmapImageWidth % nMono8bpp)			// 3  Calculating the bytes for black and white image
			{
				// nMono8bpp =8

				nByteBlackAndWhite = nBitmapImageWidth / nMono8bpp; // 102
			}
			else
			{
				nByteBlackAndWhite = nBitmapImageWidth / nMono8bpp + 1;
			}
			nPaddingBlackAndWhite = nByteBlackAndWhite % nMultiple4Check;
			if (nPaddingBlackAndWhite)				//Calculating padding have to be done in converted black and white image
			{
				nPaddingBlackAndWhite = nMultiple4Check - nPaddingBlackAndWhite;
			}
			else
			{
				nPaddingBlackAndWhite = 0;
			}
			//Ends the calculation of calculating linelength adn padding bytes for monochrome/black and white image

			//Calculation of pixel array for black and white image/Monochrome begins

			if (objFileToRead.fnCreate(argv[2], GENERIC_READ, OPEN_EXISTING) == FALSE)//Creating a handle to Source image file
			{
				dwErrCode = GetLastError();
				_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));
				_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());
				return EXIT_FAILURE;
			}

			/*
			 * Creating a handle to write to the,"argv[3]',i.e the destination file !
			 */
			if (objFileToWrite.fnCreate(argv[3], GENERIC_WRITE, CREATE_ALWAYS) == FALSE)
			{
				dwErrCode = GetLastError();
				_tprintf(_T("\n\tThe error message:-%ws"), objErrorHandler.fngeterrordescription(dwErrCode));
				_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());
				return EXIT_FAILURE;
			}

			int nFlag = 2;
			//Flag used so that on starting to read convert and write the data to destination,the read handle read the values after header.
			//Flag used so that header is copied only once in the beginning.
			BYTE bTupleColoured[512] = { 0 };
			int offsetpixelarray = objBmp.fnreturnOffsetpixelarray();
			/*
			 *		Below is the code to compute pixel array for the monochrome image!
			 */
			while (dwBitmapHeight)
			{
				
				int nSectors = ((nBitmapImageWidth * 3) / 504);				// 4
				int nAdditional = ((nBitmapImageWidth * 3) % 504);			// 441
				BYTE bTupleBinary[8] = { 0 };
				int nIteratorbTupleBinary = 0;
				
				  //  0x36

				if (nFlag == 2)
				{
					DWORD dwptr = SetFilePointer(objFileToRead.fnGetHandle(), offsetpixelarray , NULL, FILE_BEGIN);
					if (dwptr == INVALID_SET_FILE_POINTER)
					{
						dwErrCode = GetLastError();
						//Retriving the last error code
						_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));
						//Retriving error message
						_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());
						//Retriving error code
						return EXIT_FAILURE;
					}
					--nFlag;
				}
				if (nFlag == 1)
				{

					if (objFileToWrite.fnWrite(bMonoReadBuffer, nOffsetPixelArrayMono) == FALSE)
					{
						objFileToWrite.fnClose();
						dwErrCode = GetLastError();
						_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));
						_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());
						return EXIT_FAILURE;
					}
					--nFlag;
				}
				__int32 nIteratorbTupleColoured = 0;//Iterator for the buffer that is storing the value where the current is pointing.
				while (nSectors)
				{
					/*
					 * Reading one row of source ("argv[2]") pixel array to "bTupleColoured" buffer.
					 */
					int i = 0; //For filling the value into bTupleColoured after converting it to decimal(Iterator)
					if (objFileToRead.fnRead(bTupleColoured, 504) == FALSE)
					{
						objFileToRead.fnClose();
						objFileToWrite.fnClose();
						dwErrCode = GetLastError();
						_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));
						_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());
						return EXIT_FAILURE;
					}
					offsetpixelarray += 0x1f8;
					DWORD dwptr = SetFilePointer(objFileToRead.fnGetHandle(), offsetpixelarray,NULL, FILE_BEGIN);
					if (dwptr == INVALID_SET_FILE_POINTER)
					{
						dwErrCode = GetLastError();
						//Retriving the last error code
						_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));
						//Retriving error message
						_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());
						//Retriving error code
						return EXIT_FAILURE;
					}
					
					for (int j = 0; j < 168; j++)
					   /*
						* 168??
						* 504 is size of bTupleColoured
						* Have to convert 24 byte to 1 byte means 1 pixel i.e BGR to Linear
						* have 504 values each of which 
						*  0 1 2 3 4 ..... 502 503 504
						*  B G R B G...... B   G   R
						* 504 / 3 = 168 
						* As above for loop will run once for every BGR value
						*/ 
					{
						
						float LinearIntensity = LinearIntesityValue(bTupleColoured[(nIteratorbTupleColoured) % 504],
							bTupleColoured[(nIteratorbTupleColoured + 1) % 504], bTupleColoured[(nIteratorbTupleColoured + 2) % 504]);
						//fillBuffer(Linear, bTupleBinary,nIteratorbTupleBinary);
						if (LinearIntensity > fThreshold)
							bTupleBinary[nIteratorbTupleBinary % 8] = nWhite;
						else
							bTupleBinary[nIteratorbTupleBinary % 8] = nBlack;
						nIteratorbTupleBinary++;
						nIteratorbTupleColoured += 3;
						if (nIteratorbTupleColoured % 24 == 0)
						{
							int nDecimalValue = hexadecimalToDecimal(bTupleBinary);
							bTupleColoured[i] = nDecimalValue;
							i++;
						}
					}
					if (objFileToWrite.fnWrite(bTupleColoured, 21) == FALSE)
						//To write HEADERS to destination file
					{
						objFileToWrite.fnClose();//Closing the handle opened for writing to the file
						dwErrCode = GetLastError();//Retriving the last error code
						_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
						_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());//Retriving error code
						return EXIT_FAILURE;
					}
					nSectors--;
				}
				if(nAdditional)
				{
					int i = 0;
					int nValuetoWrite = nAdditional / 24;
					nAdditional = (nAdditional - (nAdditional % 24));
					// nAdditional % 24 ??
					// As nAdditional contains padding bytes also that's why it is deleted right away.
					DWORD dwptr = SetFilePointer(objFileToRead.fnGetHandle(), offsetpixelarray, NULL, FILE_BEGIN);
					if (dwptr == INVALID_SET_FILE_POINTER)
					{
						dwErrCode = GetLastError();
						//Retriving the last error code
						_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));
						//Retriving error message
						_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());
						//Retriving error code
						return EXIT_FAILURE;
					}
					offsetpixelarray = offsetpixelarray + nAdditional;
					// Since last bytes are for padding
					// (nAdditional - (nAdditional % 24))??
					// Because, nAddtional also have some addtional bytes apart from its 24 byte pairs to be converted to
					// equivalent 1 byte..which is actually our padding bytes

					if (objFileToRead.fnRead(bTupleColoured, nAdditional) == FALSE)
					{
						objFileToRead.fnClose();
						objFileToWrite.fnClose();
						dwErrCode = GetLastError();
						_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));
						_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());
						return EXIT_FAILURE;
					}
					for (int j = 0; j < (nAdditional / 3); j++)
						// nAdditional / 3 ??
						// Because, the above loop has to be executed in multiple of 3.
					{
						float LinearIntensity = LinearIntesityValue(bTupleColoured[(nIteratorbTupleColoured) % 504],
							bTupleColoured[(nIteratorbTupleColoured + 1) % 504], bTupleColoured[(nIteratorbTupleColoured + 2) % 504]);
						//fillBuffer(Linear, bTupleBinary,nIteratorbTupleBinary);
						if (LinearIntensity > fThreshold)
							bTupleBinary[nIteratorbTupleBinary % 8] = nWhite;
						else
							bTupleBinary[nIteratorbTupleBinary % 8] = nBlack;
						nIteratorbTupleBinary++;
						nIteratorbTupleColoured += 3;
						if (nIteratorbTupleColoured % 24 == 0)
						{
							int nDecimalValue = hexadecimalToDecimal(bTupleBinary);
							bTupleColoured[i] = nDecimalValue;
							i++;
						}
					}
					if (objFileToWrite.fnWrite(bTupleColoured, nValuetoWrite) == FALSE)
						//To write HEADERS to destination file
					{
						objFileToWrite.fnClose();//Closing the handle opened for writing to the file
						dwErrCode = GetLastError();//Retriving the last error code
						_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
						_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());//Retriving error code
						return EXIT_FAILURE;
					}
				}
				if (nPaddingBlackAndWhite)
				{
					//BYTE bPadding[10] = { 0 };
					nIteratorbTupleColoured = 0;
					memset(bTupleColoured, 0, sizeof(bTupleColoured));
					memset(bTupleBinary,0,sizeof(bTupleBinary));
					int i=0;
					DWORD dwptr = SetFilePointer(objFileToRead.fnGetHandle(), offsetpixelarray, NULL, FILE_BEGIN);
					offsetpixelarray = offsetpixelarray + (((nBitmapImageWidth % 4) * 3) + (nBitmapImageWidth % 4));
					if (dwptr == INVALID_SET_FILE_POINTER)
					{
						dwErrCode = GetLastError();
						//Retriving the last error code
						_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));
						//Retriving error message
						_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());
						//Retriving error code
						return EXIT_FAILURE;
					}
					
					if (objFileToRead.fnRead(bTupleColoured, (nBitmapImageWidth % 4) * 3) == FALSE)
					{
						objFileToRead.fnClose();
						objFileToWrite.fnClose();
						dwErrCode = GetLastError();
						_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));
						_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());
						return EXIT_FAILURE;
					}
					for (int j = 0; j < (nBitmapImageWidth % 4); j++)
					{
						float LinearIntensity = LinearIntesityValue(bTupleColoured[(nIteratorbTupleColoured) % 504],
							bTupleColoured[(nIteratorbTupleColoured + 1) % 504], bTupleColoured[(nIteratorbTupleColoured + 2) % 504]);
						//fillBuffer(Linear, bTupleBinary,nIteratorbTupleBinary);
						if (LinearIntensity > fThreshold)
							bTupleBinary[nIteratorbTupleBinary % 8] = nWhite;
						else
							bTupleBinary[nIteratorbTupleBinary % 8] = nBlack;
						nIteratorbTupleBinary++;
						nIteratorbTupleColoured += 3;
						if (nIteratorbTupleColoured == (nBitmapImageWidth % 4) * 3)
						{
							int nDecimalValue = hexadecimalToDecimal(bTupleBinary);
							bTupleColoured[i] = nDecimalValue;
							i++;
							memset(bTupleBinary, 0, sizeof(bTupleBinary));
							nDecimalValue = hexadecimalToDecimal(bTupleBinary);
							bTupleColoured[i] = nDecimalValue;
						}
					}
					if (objFileToWrite.fnWrite(bTupleColoured, 2) == FALSE)
						//To write HEADERS to destination file
					{
						objFileToWrite.fnClose();//Closing the handle opened for writing to the file
						dwErrCode = GetLastError();//Retriving the last error code
						_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
						_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());//Retriving error code
						return EXIT_FAILURE;
					}
				}
				dwBitmapHeight--;
			}

		}
		}
	}
	else
	{
		cout << "Usage: <Option> <Source> <Destination>" << endl;
		cout << "Options:" << endl;
		cout << "-h1 : Bitmap file header :   <-H1> <Source.bmp>" << endl;
		cout << "-h2 : DIB header :           <-H2> <Source.bmp>" << endl;
		cout << "-i  : Basic information :    <-I> <Source.bmp>" << endl;
		cout << "-p  : pixel array :          <-P> <Source.bmp>" << endl;
		cout << "-o  : Original image copy :  <-O> <Source.bmp> <Destination.bmp> " << endl;
		cout << "-bw : Monochrome image :     <-BW> <Source.bmp> <Destination.bmp> " << endl;
	}
}

void copyToStructure(BMPstructure *pBMPstructure, BYTE bReadBuffer[])
{
	int nReadOffset = 0;//To copy particular bytes from buffer to BMPstructure.h's parameters

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

}

float GammaExpansion(float ColorValue)
{
	ColorValue /= 255;
	if (ColorValue <= 0.04045)
	{
		ColorValue /= 12.92;
	}

	else {
		ColorValue = pow(((ColorValue + 0.055) / 1.055), 2.4);
	}
	return ColorValue;
}

int hexadecimalToDecimal(BYTE bTupleBinary[])
{
	int nDecimalValue = 0;
	int j = 7;//Iterator to convert bits to binary
	int nIteratorbTupleBinary = 0;
	while (j >= 0)
	{
		int nValue;
		nValue = bTupleBinary[nIteratorbTupleBinary] * pow(2, j);
		nDecimalValue += nValue;
		j--;
		nIteratorbTupleBinary++;
	}
	return nDecimalValue;
}

float LinearIntesityValue(float Blue, float Green, float Red)
{
	Blue = GammaExpansion(Blue);//To remove gamma compression function
	Green = GammaExpansion(Green);
	Red = GammaExpansion(Red);
	float LinearIntensity = Red * 0.2126 + Green * 0.7152 + Blue * 0.0722;
	return LinearIntensity;
}
/*void fillBuffer(float Linear, BYTE * bTupleBinary,int nIteratorbTupleBinary)
{
	if (Linear > fThreshold)
	{
		bTupleBinary[nIteratorbTupleBinary % 8] = nWhite;
		++nIteratorbTupleBinary;
	}
	else {
		bTupleBinary[nIteratorbTupleBinary % 8] = nBlack;
		++nIteratorbTupleBinary;
	}
}*/