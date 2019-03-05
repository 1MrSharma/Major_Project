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
	void setFiletype(WORD Filetype)
	{
		m_wFiletype = Filetype;
	}
	void setSizeBMP(DWORD SizeBMP)
	{
		m_dwSizeBMP = SizeBMP;
	}
	void setReserved1(WORD Reserved1)
	{
		m_wReserved1 = Reserved1;
	}
	void setReserved2(WORD Reserved2)
	{
		m_wReserved2 = Reserved2;
	}
	void setOffsetpixelarray(DWORD Offsetpixelarray)
	{
		m_dwOffsetpixelarray = Offsetpixelarray;
	}
	void setSizebitmapinfoheader(DWORD Sizebitmapinfoheader)
	{
		m_dwSizebitmapinfoheader = Sizebitmapinfoheader;
	}
	void setBitmapwidth(INT32 Bitmapwidth)
	{
		m_nBitmapwidth = Bitmapwidth;
	}
	void setBitmapheight(INT32 Bitmapheight)
	{
		m_nBitmapheight = Bitmapheight;
	}
	void setColorplanes(WORD Colorplanes)
	{
		m_wColorplanes = Colorplanes;
	}
	void setColordepth(WORD Colordepth)
	{
		m_wColordepth = Colordepth;
	}
	void setCompressionmethod(DWORD Compressionmethod)
	{
		m_dwCompressionmethod = Compressionmethod;
	}
	void setRawimagesize(DWORD Rawimagesize)
	{
		m_dwRawimagesize = Rawimagesize;
	}
	void setHorizontalresolution(DWORD Horizontalresolution)
	{
		m_dwHorizontalresolution = Horizontalresolution;
	}
	void setVerticalresolution(DWORD Verticalresolution)
	{
		m_dwVerticalresolution = Verticalresolution;
	}
	void setColorpallete(DWORD Colorpallete)
	{
		m_dwColorpallete = Colorpallete;
	}
	void setImportantcolors(DWORD Importantcolors)
	{
		m_dwImportantcolors = Importantcolors;
	}
	WORD getFiletype()
	{
		return m_wFiletype;
	}
	DWORD getSizeBMP()
	{
		return m_dwSizeBMP;
	}
	WORD getReserved1()
	{
		return m_wReserved1;
	}
	WORD getReserved2()
	{
		return m_wReserved2;
	}
	DWORD getOffsetpixelarray()
	{
		return m_dwOffsetpixelarray;
	}
	DWORD getSizebitmapinfoheader()
	{
		return m_dwSizebitmapinfoheader;
	}
	INT32 getBitmapwidth()
	{
		return m_nBitmapwidth;
	}
	INT32 getBitmapheight()
	{
		return m_nBitmapheight;
	}
	WORD getColorplanes()
	{
		return m_wColorplanes;
	}
	WORD getColordepth()
	{
		return m_wColordepth;
	}
	DWORD getCompressionmethod()
	{
		return m_dwCompressionmethod;
	}
	DWORD getRawimagesize()
	{
		return m_dwRawimagesize;
	}
	DWORD getHorizontalresolution()
	{
		return m_dwHorizontalresolution;
	}
	DWORD getVerticalresolution()
	{
		return m_dwVerticalresolution;
	}
	DWORD getColorpallete()
	{
		return m_dwColorpallete;
	}
	DWORD getImportantcolors()
	{
		return m_dwImportantcolors;
	}

};

#endif