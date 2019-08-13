#include "pch.h"
#include <iostream>
#include<tchar.h>
#include<tchar.h>
#include<cstdio>
#include<vector>
#include<algorithm>
#include"Helper.h"
#include"BMP.h"
#include"File.h"
#include"Error.h"
#include"Cmdline.h"
#include<cmath>

void copyToStructure(BMPstructure*, BYTE[]);

using namespace std;

const int nBUFFERSIZE = 1024;
const int nBUFFERSIZEbMonoReadBuffer = 62;
const char chmagicCharacter[10] = ".bmp$";
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
const int nBitValueMonochromeOne = 1;
const int nBitValueMonochromeZero = 0;
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


		switch (nChoice)
		{
			case 1://Bitmap info header
			{
				cout << hex << objBmp.fnreturnFiletype() << " " << objBmp.fnreturnSizeBMP() << " " << objBmp.fnreturnReserved1() << " " << objBmp.fnreturnReserved2() << " " << objBmp.fnreturnOffsetpixelarray();
				break;
			}
			case 2:// DIB header
			{
				cout << objBmp.fnreturnSizebitmapinfoheader() << " " << objBmp.fnreturnBitamapwidth() << " " << objBmp.fnreturnBitmapheight() << " " << objBmp.fnreturnColorplanes() << endl;
				cout << objBmp.fnreturnColordepth() << " " << objBmp.fnreturnCompressionmethod() << " " << objBmp.fnreturnRawimagesize() << endl;
				cout << objBmp.fnreturnHorizontalresolution() << " " << objBmp.fnreturnVerticalresolution() << " " << objBmp.fnreturnColorplanes() << " " << objBmp.fnreturnImportantcolors() << endl;
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
				DWORD bsizeofBMP = pBMPstructure->fngetSizeBMP();
				bsizeofBMP -= objBmp.fnreturnOffsetpixelarray();
				int nSectors = bsizeofBMP / 1024;
				int nAdditional = bsizeofBMP % 1024;
				int nFlagPixelArray = 1;

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
				int flag = 1;
				while (nSectors)
				{

					if (objFileToRead.fnRead(bReadBuffer, 1024) == FALSE)
					{
						objFileToRead.fnClose();
						objFileToWrite.fnClose();
						dwErrCode = GetLastError();//Retriving the last error code
						_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
						_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());//Retriving error code
						_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
						return EXIT_FAILURE;
					}
					int nInitialLower = 0, nInitialHigher = 16;
					for (int nIteratorRows = 0; nIteratorRows < 64; nIteratorRows++)//64 because the size of bReadbuffer is 1024
					{
						for (int nIteratorColumn = nInitialLower; nIteratorColumn < nInitialHigher; nIteratorColumn++)
						{
							cout << hex << (int)bReadBuffer[nIteratorColumn] << " ";
						}
						nInitialLower += 16; nInitialHigher += 16;
						cout << "\n";
						if (flag == 1)
						{
							char Choice;
							cout << "Do you want to see complete pixel array ? [Y/N] " << endl;
							cin >> Choice;
							if (Choice == 'N' || Choice == 'n')
							{
								return 0;
							}
							--flag;
						}
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
				DWORD bsizeofBMP = pBMPstructure->fngetSizeBMP();//Getting the size of BMP image 
				int nSectors = bsizeofBMP / CFile::m_knSECTORSIZE;//Calculating how many sectors does the image contain for size eqivalent to m_knSECTORSIZE
				int nAdditional = bsizeofBMP % CFile::m_knSECTORSIZE;//Calculating how many remaining bytes left after calculating sectors
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
				int nRowSize = ((nBitmapImageWidth + 31) / 32) * 4;//Calculation of row size formula according wikipedia
				DWORD dwBitmapHeight = objBmp.fnreturnBitmapheight();
				int nSizeRawBitmap = nRowSize * dwBitmapHeight;
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

				//Calculating the linelength and padding bytes of coloured image


				int nLineLengthColoured, nPaddingColoured;

				if (objBmp.fnreturnColordepth() == nColorDepth24)
				{
					int nBitmapwidth = ((objBmp.fnreturnBitamapwidth() * nPixelColorValue) % nMultiple4Check);
					if (nBitmapwidth != 0)
					{
						nPaddingColoured = nMultiple4Check - nBitmapwidth;
					}
					else
					{
						nPaddingColoured = 0;
					}

					nLineLengthColoured = (objBmp.fnreturnBitamapwidth() *  nPixelColorValue) + nPaddingColoured;//length of 1 line including padding bytes

				}

				//End of calculating line length of linelength and padding bytes of coloured image


				//Calculating the linelength and padding bytes for required monochrome/black and white image


				int nByteBlackAndWhite, nPaddingBlackAndWhite, nLineLengthBlackAndWhite;

				if ((objBmp.fnreturnBitamapwidth() % nMono8bpp) != 0)			//Calculating the bytes for black and white image
				{
					nByteBlackAndWhite = objBmp.fnreturnBitamapwidth() / nMono8bpp;
				}
				else
				{
					nByteBlackAndWhite = objBmp.fnreturnBitamapwidth() / nMono8bpp + 1;
				}
				if ((nByteBlackAndWhite % nMultiple4Check) != 0)				//Calculating padding have to be done in converted black and white image
				{
					nPaddingBlackAndWhite = nMultiple4Check - (nByteBlackAndWhite % nMultiple4Check);
				}
				else
				{
					nPaddingBlackAndWhite = 0;
				}

				nLineLengthBlackAndWhite = nByteBlackAndWhite + nPaddingBlackAndWhite;//Length of 1 line have to be there in black and white image

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


				int fFFlag = 1;//Flag used so that header is copied only once in the beginning.
				int nFlag = 1;//Flag used so that on starting to read convert and write the data to destination,the read handle read the values after header.
				BYTE bTupleColoured[4096] = { 0 };
				int nPixelRowsBMP = objBmp.fnreturnBitmapheight();
				int nPixelColumnBMP = objBmp.fnreturnBitamapwidth();
				int looprunning = nPixelColumnBMP / 8;
				//int nbitConversionLoop = nLineLengthColoured / nByteBlackAndWhite;


				/*
				 * Below is the code to compute pixel array for the monochrome image!
				 */
				while (nPixelRowsBMP)
				{
					__int32 nIteratorbTupleColoured = 0;//Iterator for the buffer that is storing the value where the current is pointing.

					if (fFFlag == 1) {
						/*
					 * Write the "bMonoReadBuffer",which has both the header values,i.e(Bitmap & DIB header).
					 * The "nOffsetPixelArrayMono",is the constant values for the header of monochrome image which is,62.
					 */
						if (objFileToWrite.fnWrite(bMonoReadBuffer, nOffsetPixelArrayMono) == FALSE)
						{
							objFileToWrite.fnClose();
							dwErrCode = GetLastError();
							_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));
							_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());
							return EXIT_FAILURE;
						}
						--fFFlag;
					}
					//"nFlag" used,so that the code inside "if" statement is compiled and runned only once.
					if (nFlag == 1)
					{

						/*
						 * To copy the data of the file (only pixel array) to the buffer.
						 * "SetFilePointer" WinAPI is used !
						 */
						DWORD dwptr = SetFilePointer(objFileToRead.fnGetHandle(), objBmp.fnreturnOffsetpixelarray(), NULL, FILE_BEGIN);

						//Check if it is pointing to the desired or giving some garbage value
						if (dwptr == INVALID_SET_FILE_POINTER)
						{
							dwErrCode = GetLastError();																		//Retriving the last error code
							_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode)); //Retriving error message
							_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());							//Retriving error code
							return EXIT_FAILURE;
						}
						--nFlag;
					}

					/*
					 * Reading one row of source ("argv[2]") pixel array to "bTupleColoured" buffer.
					 */
					if (objFileToRead.fnRead(bTupleColoured, nLineLengthColoured) == FALSE)
					{
						objFileToRead.fnClose();
						objFileToWrite.fnClose();
						dwErrCode = GetLastError();
						_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));
						_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());
						return EXIT_FAILURE;
					}

					//Buffer to have the converted 24 bit value to 1 bit,for every row in each 24 bit.
					BYTE bTupleBinary[8] = { 0 };
					int nIteratorbTupleBinary = 0;

					//Final buffer which will be copied to the destination file.
					BYTE bWriteBW[128] = { 0 };
					int nIteratorbWriteBW = 0;

					int loop = nByteBlackAndWhite;


					/*
					 * The below loop is running for the linelength of monochrome, removing the padding.
					 */

					while (loop)
					{
						int nbitConversionLoop = 8;//Have to initialize it for every loop as it is converting 3 byte to 1 byte

						while (nbitConversionLoop)
						{

							//Rgb to bit conversion starts


							//Reading 24 bit from the bTupleColoured buffer and converting each byte to a bit
							/* Below is the Diagrammatic representation
							 *
							 * First row of pixels is copied to, bTupleColoured.Suppose for the image "24.bmp","2460 bytes" are copied !
							 *    ___________________
							 *	  |	 B    G    R    |
							 *    |-----------------|
							 *	  |	 0    1    2    |
							 *	  |	 3    4    5    |
							 *	  |	 6    7    8    |
							 *	  |	 9    10   11   |
							 *	  |	 12   13   14   |
							 *	  |	 .........      |
							 *	  |	 .........      |
							 *	  |	 2457 2458 2459 |
							 *    |-----------------|
							 *
							 * Every color means,"BLUE","GREEN" or "RED" have the maximum value "255"!
							 * And every pixel contains, above three values BGR,we have to take average of the three color values.
							 * Have to divide it with,"nTotalValuePixel",i.e the addition of all the three color values,i.e 765 !
							 * After division we get the "rAverage",which is the
							 * Then compare "rAverage" with "fThreshold"(0.5) to get the binary equivalent.
							 *
							 */
							float_t rAverage = ((float)(bTupleColoured[nIteratorbTupleColoured] + bTupleColoured[nIteratorbTupleColoured + 1] + bTupleColoured[nIteratorbTupleColoured + 2]) / nTotalValuePixel);
							if (rAverage > fThreshold)
							{
								bTupleBinary[nIteratorbTupleBinary % 8] = nBitValueMonochromeOne;
								++nIteratorbTupleBinary;
							}
							else {
								bTupleBinary[nIteratorbTupleBinary % 8] = nBitValueMonochromeZero;
								++nIteratorbTupleBinary;
							}
							nIteratorbTupleColoured += 3;
							//End of Reading 24 bit and converting it into 1 bit

							/*
							*After 1st iteration with the while loop from our source image "24.bmp" i.e the source
							*The buffer "bTupleBinary",looks like below
							*---------------------------------
							*| 1 | 1 | 1 | 1 | 1 | 1 | 1 | 1 |
							*---------------------------------
							* Next,converting this particular code to the hexadecimal equivalent,which is "0xFF".
							*/

							if (nIteratorbTupleColoured % 24 == 0)
							{
								//Code to convert the bTupleBinary values to decimal
								int nDecimalValue = 0;
								int j = 7;
								nIteratorbTupleBinary = 0;
								while (j >= 0)
								{
									int nValue;
									nValue = bTupleBinary[nIteratorbTupleBinary] * pow(2, j);
									nDecimalValue += nValue;
									j--;
									nIteratorbTupleBinary++;
								}
								bWriteBW[nIteratorbWriteBW] = nDecimalValue;
								++nIteratorbWriteBW;
							}

							//Rgb to bit conversion ends
							--nbitConversionLoop;
						}

						--loop;
					}
					bWriteBW[nIteratorbWriteBW] = 0x0e;
					bWriteBW[nIteratorbWriteBW + 1] = 0x00;

					if (objFileToWrite.fnWrite(bWriteBW, nLineLengthBlackAndWhite) == FALSE)//To write HEADERS to destination file
					{
						objFileToWrite.fnClose();//Closing the handle opened for writing to the file
						dwErrCode = GetLastError();//Retriving the last error code
						_tprintf(_T("\n\tThe error message:-%ws\n"), objErrorHandler.fngeterrordescription(dwErrCode));//Retriving error message
						_tprintf(_T("\n\tThe error code:-%d"), objErrorHandler.fngetErrCode());//Retriving error code
						return EXIT_FAILURE;
					}
					--nPixelRowsBMP;
				}

			}

		}
	}
	else
	{
		cout << "Usage: <Option> <Source> <Destination>" << endl;
		cout << "Options:" << endl;
		cout << "-h1 : Bitmap file header :   <-h1> <Source.bmp>" << endl;
		cout << "-h2 : DIB header :           <-h2> <Source.bmp>" << endl;
		cout << "-i  : Basic information :    <-i> <Source.bmp>" << endl;
		cout << "-p  : pixel array :          <-p> <Source.bmp>" << endl;
		cout << "-o  : Original image copy :  <-o> <Source.bmp> <Destination.bmp> " << endl;
		cout << "-bw : Monochrome image :     <-bw> <Source.bmp> <Destination.bmp> " << endl;
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