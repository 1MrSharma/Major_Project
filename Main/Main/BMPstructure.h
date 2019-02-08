#pragma once
#include<Windows.h>
struct BMPstructure
{
	WORD m_wFiletype;
	DWORD m_dwSizeBMP;
	WORD m_wReserved1;
	WORD m_wReserved2;
	DWORD m_dwOffsetpixelarray;
	DWORD m_dwSizebitmapinfoheader;
	INT32 m_nBitmapwidth;
	INT32 m_nBitmapheight;
	WORD m_wColorplanes;
	WORD m_wColordepth;
	DWORD m_dwCompressionmethod;
	DWORD m_dwRawimagesize;
	DWORD m_dwHorizontalresolution;
	DWORD m_dwVerticalresolution;
	DWORD m_dwColorpallete;
	DWORD m_dwImportantcolors;
}BMPstructurevariable;