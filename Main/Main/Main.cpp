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
const int nBUFFERSIZE = 1024;
using namespace std;

int main(int argc, TCHAR *argv[])
{
	if (argc >= 3)
	{
		CCmdLine obj_cmdline;
		char chMagiccharacter[10] = ".bmp";
		obj_cmdline.Addoptions("-h1");//Option -h1 pushed to a private attribute (i.e) 
		obj_cmdline.Addoptions("-h2");//Option -h2 pushed to OptionsList of CCmdLine class
		obj_cmdline.Addoptions("-i");//Option -i pushed to OptionsList of CCmdLine class
		obj_cmdline.Addoptions("-p");//Option -p pushed to OptionsList of CCmdLine class
		obj_cmdline.Addoptions("-o");//Option -o pushed to OptionsList of CCmdLine class 
		obj_cmdline.Addoptions("-bw");//Option -bw pushed to OptionsList of CCmdLine class
		obj_cmdline.Addoptions("-BW");
		if (obj_cmdline.Searchoptionslist(argv[1]) == FALSE)
		{
			return EXIT_FAILURE;
		}
		if (obj_cmdline.Checkextension(argv[2], chMagiccharacter) == FALSE)
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
		if (obj_cmdline.GetCurrentOption() == "-h1") { nChoice = 1; }//1 if -h1 i.e Bitmap info header
		if (obj_cmdline.GetCurrentOption() == "-h2") { nChoice = 2; }//2 if -h2 i.e DIB header
		if (obj_cmdline.GetCurrentOption() == "-i") { nChoice = 3; }//3 if -i i.e general information
		if (obj_cmdline.GetCurrentOption() == "-p") { nChoice = 4; }//4 if -p i.e pixel array
		if (obj_cmdline.GetCurrentOption() == "-o") { nChoice = 5; }//5 if -o i.e original image copy
		if (obj_cmdline.GetCurrentOption() == "-bw") { nChoice = 6; }//6 if -bw i.e black and white image copy
		if (obj_cmdline.GetCurrentOption() == "-BW") { nChoice = 6; }
		switch (nChoice)
		{
			case 1://Bitmap info header
			{
				cout << hex << obj_BMP.fnreturnFiletype() << " " << obj_BMP.fnreturnSizeBMP() << " " << obj_BMP.fnreturnReserved1() << " " << obj_BMP.fnreturnReserved2() << " " << obj_BMP.fnreturnOffsetpixelarray();
				break;
			}
			case 2:// DIB header
			{
				cout << obj_BMP.fnreturnSizebitmapinfoheader() << " " << obj_BMP.fnreturnBitamapwidth() << " " << obj_BMP.fnreturnBitmapheight() << " " << obj_BMP.fnreturnColorplanes() << endl;
				cout << obj_BMP.fnreturnColordepth() << " " << obj_BMP.fnreturnCompressionmethod() << " " << obj_BMP.fnreturnRawimagesize() << endl;
				cout << obj_BMP.fnreturnHorizontalresolution() << " " << obj_BMP.fnreturnVerticalresolution() << " " << obj_BMP.fnreturnColorplanes() << " " << obj_BMP.fnreturnImportantcolors() << endl;
				break;
			}
			case 3://general information
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
			case 4://pixel array
			{
				DWORD bsizeofBMP = pBMPstructure->fngetSizeBMP();
				bsizeofBMP -= obj_BMP.fnreturnOffsetpixelarray();
				int nSectors = bsizeofBMP / 1024;
				int nAdditional = bsizeofBMP % 1024;
				int nFlagPixelArray = 1;

				if (obj_file_to_read.fnCreate(argv[2], GENERIC_READ, OPEN_EXISTING) == FALSE)
				{
					dwErrCode = GetLastError();//Retriving the last error code
					_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
					_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
					_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
					return EXIT_FAILURE;
				}
				DWORD dwptr = SetFilePointer(obj_file_to_read.fnGetHandle(), obj_BMP.fnreturnOffsetpixelarray(), NULL, FILE_BEGIN);
				if (dwptr == INVALID_SET_FILE_POINTER)
				{
					dwErrCode = GetLastError();//Retriving the last error code
					_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
					_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
					return EXIT_FAILURE;
				}
				int flag = 1;
				while (nSectors)
				{

					if (obj_file_to_read.fnRead(bReadBuffer, 1024) == FALSE)
					{
						obj_file_to_read.fnClose();
						obj_file_to_write.fnClose();
						dwErrCode = GetLastError();//Retriving the last error code
						_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
						_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
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
				if (obj_file_to_read.fnRead(bReadBuffer, nAdditional) == FALSE)
				{
					obj_file_to_read.fnClose();
					obj_file_to_write.fnClose();
					dwErrCode = GetLastError();//Retriving the last error code
					_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
					_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
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
			case 6://black and white image copy
			{
				BYTE bMonoReadBuffer[nBUFFERSIZE] = { 0 };
				//Creating header for black and white image
				int nBitmapImageWidth = pBMPstructure->fngetBitmapwidth();//Structure which returm the image width
				int nRowSize = ((nBitmapImageWidth + 31) / 32) * 4;//Calculation of row size 
				int nSizeRawBitmap = nRowSize * (pBMPstructure->fngetBitmapheight());
				int nSizeBMP = nSizeRawBitmap + 62;
				WORD filetype = pBMPstructure->fngetFiletype();
				//Bitmap file header starts
				memcpy(bMonoReadBuffer + 0, &filetype, 2);
				//bMonoReadBuffer[2] = nSizeBMP;//Error Debugging
				memcpy(bMonoReadBuffer + 2, &nSizeBMP, 2);
				bMonoReadBuffer[6] = pBMPstructure->fngetReserved1();

				bMonoReadBuffer[8] = pBMPstructure->fngetReserved2();
				bMonoReadBuffer[10] = 0x3E;

				//Bitmap file header ends
				//DIB Header starts
				bMonoReadBuffer[14] = 0x28;
				memcpy(bMonoReadBuffer + 18, &nBitmapImageWidth, 2);
				DWORD bitmapheight = pBMPstructure->fngetBitmapheight();
				memcpy(bMonoReadBuffer + 22, &bitmapheight, 4);
				bMonoReadBuffer[26] = pBMPstructure->fngetColorplanes(); bMonoReadBuffer[28] = 1;
				bMonoReadBuffer[30] = pBMPstructure->fngetCompressionmethod();
				memcpy(bMonoReadBuffer + 34, &nSizeRawBitmap, 4);
				bMonoReadBuffer[38] = pBMPstructure->fngetHorizontalresolution(); bMonoReadBuffer[42] = pBMPstructure->fngetVerticalresolution();
				bMonoReadBuffer[46] = pBMPstructure->fngetColorpalette(); bMonoReadBuffer[50] = pBMPstructure->fngetImportantcolors();
				bMonoReadBuffer[54] = 0x00; bMonoReadBuffer[55] = 0x00; bMonoReadBuffer[56] = 0x00; bMonoReadBuffer[57] = 0x00;
				bMonoReadBuffer[58] = 0xff; bMonoReadBuffer[59] = 0xff; bMonoReadBuffer[60] = 0xff; bMonoReadBuffer[61] = 0x00;
				//DIB Header ends

				//End of creating header for black and white
				if (obj_file_to_write.fnCreate(argv[3], GENERIC_WRITE, CREATE_ALWAYS) == FALSE)//Craeting a handle to destination image file
				{
					dwErrCode = GetLastError();//Retriving the last error code
					_tprintf(_T("\n\tThe error message:-%ws"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
					_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
					_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
					return EXIT_FAILURE;
				}
				if (obj_file_to_write.fnWrite(bMonoReadBuffer, 62) == FALSE)//To write HEADERS to destination file
				{
					obj_file_to_write.fnClose();//Closing the handle opened for writing to the file
					dwErrCode = GetLastError();//Retriving the last error code
					_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
					_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
					return EXIT_FAILURE;
				}
				/*
				//Calculating the linelength and padding bytes of coloured image
				int nLineLengthColoured, nPaddingColoured;
				if (obj_BMP.fnreturnColordepth() == 24)//Checking if the color depth(bits per pixel)
				{
					int nBitmapwidth = ((obj_BMP.fnreturnBitamapwidth() * 3) % 4);
					if (nBitmapwidth != 0)//Calculating padding for coloured image i.e our source image 
					{
						nPaddingColoured = 4 - nBitmapwidth;
					}
					else
					{
						nPaddingColoured = 0;
					}
					nLineLengthColoured = (obj_BMP.fnreturnBitamapwidth() * 3) + nPaddingColoured;//length of 1 line including padding bytes
				}
				//End of calculating line length of linelength and padding bytes of coloured image
				//Calculating the linelength and padding bytes for required monochrome/black and white image
				int nByteBlackAndWhite, nPaddingBlackAndWhite, nLineLengthBlackAndWhite;
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
				else
				{
					nPaddingBlackAndWhite = 0;
				}
				nLineLengthBlackAndWhite = nByteBlackAndWhite + nPaddingBlackAndWhite;//Length of 1 line have to be there in black and white image
				//Ends the calculation of calculating linelength adn padding bytes for monochrome/black and white image
				//Calculation of pixel array for black and white image/Monochrome begins

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


				BYTE bTupleColoured[3000] = { 0 };
				int nIteratorbTupleColoured = 0;
				BYTE bTupleBlackAndWhite[1024] = { 0 };
				int nIteratorbTupleBlackAndWhite = 0;
				BYTE bWriteBW[256] = { 0 };
				signed nPixelRowsBMP = obj_BMP.fnreturnBitmapheight();
				static signed nPixelColumnBMP = obj_BMP.fnreturnBitamapwidth();
				int looprunning = nPixelColumnBMP / 8;
				int nFlag = 1;
				if (obj_file_to_write.fnWrite(bMonoReadBuffer, 62) == FALSE)//To write HEADERS to destination file
				{
					obj_file_to_write.fnClose();//Closing the handle opened for writing to the file
					dwErrCode = GetLastError();//Retriving the last error code
					_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
					_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
					return EXIT_FAILURE;
				}
				while (nPixelRowsBMP)
				{
					if (nFlag == 1)
					{
						DWORD dwptr = SetFilePointer(obj_file_to_read.fnGetHandle(), obj_BMP.fnreturnOffsetpixelarray(), NULL, FILE_BEGIN);//SetFilePointer WinAPI
						if (dwptr == INVALID_SET_FILE_POINTER)//Check if it is pointing to the desired or giving some garbage value
						{
							dwErrCode = GetLastError();//Retriving the last error code
							_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
							_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
							return EXIT_FAILURE;
						}
						--nFlag;
					}
					if (obj_file_to_read.fnRead(bTupleColoured, nLineLengthColoured) == FALSE)
					{
						obj_file_to_read.fnClose();//Closing handle which was opened for reading via source file
						obj_file_to_write.fnClose();//closing handle which was opened for writing to destination file
						dwErrCode = GetLastError();//Retriving the last error code
						_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
						_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
						_tprintf(_T("\n---------------------------------------------------------------------------------------------"));
						return EXIT_FAILURE;
					}
					__int32 i = 0;
					while (nPixelColumnBMP)
					{
						
						float_t rAverage = (bTupleColoured[nIteratorbTupleColoured] + bTupleColoured[nIteratorbTupleColoured + 1] + bTupleColoured[nIteratorbTupleColoured + 2] )/ 765;
						if (rAverage > 0.5f)
						{
							bTupleBlackAndWhite[i] = 1 ;
							++i;
						}
						else {
							bTupleBlackAndWhite[i] = 0;
							++i;
						}
						nIteratorbTupleColoured += 3;
						--nPixelColumnBMP;
					}
					int nValue1;
					for (int iT = 0; iT < looprunning; iT++)
					{
						nValue1 = 0;
						int j = 7;
						while(j>=0)
						{
							int nValue;
							nValue = bTupleBlackAndWhite[nIteratorbTupleBlackAndWhite] * pow(2, j);
							nValue1 += nValue;
							++nIteratorbTupleBlackAndWhite;
							j--;
						}
						bWriteBW[iT] = nValue1;
					}
					int fflag = 1;
					if (nPaddingBlackAndWhite != 0)
					{
						for (int i = looprunning; i < nLineLengthBlackAndWhite; i++)
						{
							if (fflag == 1)
							{
								bWriteBW[i] = 0x0e;
								--fflag;
							}
							else
							{
								bWriteBW[i] = 0x00;
							}
						}
					}
					if (obj_file_to_write.fnWrite(bWriteBW, nLineLengthBlackAndWhite) == FALSE)//To write HEADERS to destination file
					{
						obj_file_to_write.fnClose();//Closing the handle opened for writing to the file
						dwErrCode = GetLastError();//Retriving the last error code
						_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));//Retriving error message
						_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());//Retriving error code
						return EXIT_FAILURE;
					}
				--nPixelRowsBMP;
				}
				*/
				break;


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