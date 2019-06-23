#include "pch.h"
#include "Handler.h"
#include<Windows.h>
#include<iostream>
#include"BMP.h"
#include"File.h"
#include"Error.h"
#include<tchar.h>
#include<cstdio>
#include"Helper.h"
const int nBUFFERSIZE = 1024;
void CHandler::fnDisplayBitmapInfo(TCHAR * chSource)
{
	
}

void CHandler::fnConvertMonochrome(TCHAR *chSource, TCHAR *chDestination)
{
	
	CFile 
	
	
	int nMono1 = pBMPstructure->fngetBitmapwidth();
	int nRowSize = (nMono1 + 31) / 32; nRowSize *= 4;
	int nMono3 = nRowSize * (pBMPstructure->fngetBitmapheight());
	int nMono2 = nMono3 + 62;
	bReadBuffer[0] = pBMPstructure->fngetFiletype();
	bReadBuffer[2] =nMono2;//Debugging
	bReadBuffer[6] = pBMPstructure->fngetReserved1(); 
	bReadBuffer[8] = pBMPstructure->fngetReserved2();
	bReadBuffer[10] = 0x3E;bReadBuffer[14] = 0x28;
	bReadBuffer[18] = nMono1; 
	bReadBuffer[22] = pBMPstructure->fngetBitmapheight(); 
	bReadBuffer[26] = pBMPstructure->fngetColorplanes(); bReadBuffer[28] = 1; bReadBuffer[30] = pBMPstructure->fngetCompressionmethod();
	bReadBuffer[34] = nMono3;//Debugging
	bReadBuffer[38] = pBMPstructure->fngetHorizontalresolution(); bReadBuffer[42] = pBMPstructure->fngetVerticalresolution();
	bReadBuffer[46] = pBMPstructure->fngetColorpalette(); bReadBuffer[50] = pBMPstructure->fngetImportantcolors();
	bReadBuffer[54] = 0x00;bReadBuffer[55] = 0x00;bReadBuffer[56] = 0x00;bReadBuffer[57] = 0x00;
	bReadBuffer[58] = 0xff;bReadBuffer[59] = 0xff;bReadBuffer[60] = 0xff;bReadBuffer[61] = 0x00;
	if (obj_file_to_write.fnCreate(chDestination, GENERIC_WRITE, CREATE_ALWAYS) == FALSE)
	{
		dwErrCode = GetLastError();
		_tprintf(_T("\n\tThe error message:-%ws"), obj_error_handler.fngeterrordescription(dwErrCode));
		_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());
		return;
	}
	if (obj_file_to_write.fnWrite(bReadBuffer, 62) == FALSE)//object to the converted onochrome is obj_file_to_write
	{
		obj_file_to_write.fnClose();
		dwErrCode = GetLastError();
		_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
		return;
	}
	if (obj_file_to_read.fnCreate(chSource, GENERIC_READ, OPEN_EXISTING) == FALSE)//object to source is obj_file_to_read
	{
		dwErrCode = GetLastError();
		_tprintf(_T("\n\tThe error message:-%ws"), obj_error_handler.fngeterrordescription(dwErrCode));
		_tprintf(_T("\n\tThe error code:-%d"), obj_error_handler.fngetErrCode());
		return;
	}
	DWORD dwRetVal = 0;
	UINT uRetVal = 0;
	TCHAR szTempFileName[MAX_PATH];
	TCHAR lpTempPathBuffer[MAX_PATH];
	dwRetVal = GetTempPath(MAX_PATH, lpTempPathBuffer);
	if (dwRetVal > (MAX_PATH+1) || (dwRetVal == 0))
	{
		obj_file_to_read.fnClose();
		dwErrCode = GetLastError();
		_tprintf(_T("\n\tThe error message:-%ws\n"), obj_error_handler.fngeterrordescription(dwErrCode));
		return;
	}
	uRetVal = GetTempFileName(lpTempPathBuffer, TEXT("MAIN"), 0, szTempFileName);
	
}