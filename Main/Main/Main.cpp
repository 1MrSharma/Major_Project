#include "pch.h"
#include <iostream>
#include<tchar.h>
#include<tchar.h>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
#include <iomanip>
#include"Helper.h"
#include"BMP.h"
#include"File.h"
#include"Error.h"
#include"Cmdline.h"

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


		CCmdLine objCmdline;

		objCmdline.Addoptions("-BW");

		if (objCmdline.Searchoptionslist(argv[1]) == FALSE)//Checking whether first argument is from the available options
		{
			return EXIT_FAILURE;
		}
		if (objCmdline.Checkextension(argv[2], chmagicCharacter) == FALSE)//Checking whether the second argument's extension matches the chmagicCharacter
		{
			return EXIT_FAILURE;
		}

		CBMP objBmp;
		CFile objFileToRead, objFileToWrite;
		CError objErrorHandler;
		DWORD dwErrCode;//Used for storing last error code
		BYTE bReadBuffer[nBUFFERSIZE] = { 0 };
		BMPstructure *pBMPstructure = new BMPstructure;//Creating a new BMPstructure pointer
		int nChoice;

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

		if (objCmdline.GetCurrentOption() == "-BW") { nChoice = 6; }//6 if -bw i.e black and white image copy
		switch (nChoice)
		{
		case 6:
			BYTE bMonoReadBuffer[nBUFFERSIZEbMonoReadBuffer] = { 0 };
			//Creating header for black and white image

			int nBitmapImageWidth = objBmp.fnreturnBitamapwidth();
			int nRowSize = ((nBitmapImageWidth + 31) / 32) * 4;//Calculation of row size formula according wikipedia
			DWORD dwBitmapHeight = objBmp.fnreturnBitmapheight();
			int nSizeRawBitmap = nRowSize * dwBitmapHeight;
			int nSizeBMP = nSizeRawBitmap + nOffsetPixelArrayMono;
			WORD filetype = objBmp.fnreturnFiletype();

			BYTE bTupleColoured[4096] = { 0 };


			signed nPixelRowsBMP = objBmp.fnreturnBitmapheight();
			static signed nPixelColumnBMP = objBmp.fnreturnBitamapwidth();
			int looprunning = nPixelColumnBMP / 8;
			int nFlag = 1;


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


			int fFFlag = 1;
			/*
			 * Below is the code to compute pixel array for the monochrome image!
			 */
			while (nPixelRowsBMP)
			{
				__int32 i = 0;
				__int32 nValue1;
				__int32 nIteratorbTupleColoured = 0;

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

				/*
				 * The below loop is running for the linelength of monochrome, removing the padding.
				 */
				while (looprunning)//102
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

					--nPixelColumnBMP;
				}

				//Code to calculate padding bytes for monochrome image!
				/*
				 * Here the last
				 */
				int nLoopIteratorPadding = nLineLengthColoured % nColorDepth24;
				BYTE bBufferPadding[64] = { 0 };
				nIteratorbTupleBinary = 0;
				for (int i = 0; i < nLoopIteratorPadding; i++)
				{
					if (bTupleColoured[i] == 0)
					{
						bTupleBinary[nIteratorbTupleBinary] = 0;
					}
					else
					{
						//
					}
				}


				if (objFileToWrite.fnWrite(bWriteBW, looprunning) == FALSE)//To write HEADERS to destination file
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