#ifndef __BMP_STRUCTURES_H__
#define __BMP_STRUCTURES_H__
#include<Windows.h>
struct BMPstructure
{
public:
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
public:
	void fnsetFiletype(WORD Filetype)
	{
		m_wFiletype = Filetype;
	}
	void fnsetSizeBMP(DWORD SizeBMP)
	{
		m_dwSizeBMP = SizeBMP;
	}
	void fnsetReserved1(WORD Reserved1)
	{
		m_wReserved1 = Reserved1;
	}
	void fnsetReserved2(WORD Reserved2)
	{
		m_wReserved2 = Reserved2;
	}
	void fnsetOffsetpixelarray(DWORD Offsetpixelarray)
	{
		m_dwOffsetpixelarray = Offsetpixelarray;
	}
	void fnsetSizebitmapinfoheader(DWORD Sizebitmapinfoheader)
	{
		m_dwSizebitmapinfoheader = Sizebitmapinfoheader;
	}
	void fnsetBitmapwidth(INT32 Bitmapwidth)
	{
		m_nBitmapwidth = Bitmapwidth;
	}
	void fnsetBitmapheight(INT32 Bitmapheight)
	{
		m_nBitmapheight = Bitmapheight;
	}
	void fnsetColorplanes(WORD Colorplanes)
	{
		m_wColorplanes = Colorplanes;
	}
	void fnsetColordepth(WORD Colordepth)
	{
		m_wColordepth = Colordepth;
	}
	void fnsetCompressionmethod(DWORD Compressionmethod)
	{
		m_dwCompressionmethod = Compressionmethod;
	}
	void fnsetRawimagesize(DWORD Rawimagesize)
	{
		m_dwRawimagesize = Rawimagesize;
	}
	void fnsetHorizontalresolution(DWORD Horizontalresolution)
	{
		m_dwHorizontalresolution = Horizontalresolution;
	}
	void fnsetVerticalresolution(DWORD Verticalresolution)
	{
		m_dwVerticalresolution = Verticalresolution;
	}
	void fnsetColorpallete(DWORD Colorpallete)
	{
		m_dwColorpallete = Colorpallete;
	}
	void fnsetImportantcolors(DWORD Importantcolors)
	{
		m_dwImportantcolors = Importantcolors;
	}
	WORD fngetFiletype()
	{
		return m_wFiletype;
	}
	DWORD fngetSizeBMP()
	{
		return m_dwSizeBMP;
	}
	WORD fngetReserved1()
	{
		return m_wReserved1;
	}
	WORD fngetReserved2()
	{
		return m_wReserved2;
	}
	DWORD fngetOffsetpixelarray()
	{
		return m_dwOffsetpixelarray;
	}
	DWORD fngetSizebitmapinfoheader()
	{
		return m_dwSizebitmapinfoheader;
	}
	INT32 fngetBitmapwidth()
	{
		return m_nBitmapwidth;
	}
	INT32 fngetBitmapheight()
	{
		return m_nBitmapheight;
	}
	WORD fngetColorplanes()
	{
		return m_wColorplanes;
	}
	WORD fngetColordepth()
	{
		return m_wColordepth;
	}
	DWORD fngetCompressionmethod()
	{
		return m_dwCompressionmethod;
	}
	DWORD fngetRawimagesize()
	{
		return m_dwRawimagesize;
	}
	DWORD fngetHorizontalresolution()
	{
		return m_dwHorizontalresolution;
	}
	DWORD fngetVerticalresolution()
	{
		return m_dwVerticalresolution;
	}
	DWORD fngetColorpalette()
	{
		return m_dwColorpallete;
	}
	DWORD fngetImportantcolors()
	{
		return m_dwImportantcolors;
	}

};

#endif