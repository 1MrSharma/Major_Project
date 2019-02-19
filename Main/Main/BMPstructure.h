#pragma once
#include<Windows.h>
struct BMPstructure
{
private:
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
	void setFiletype(WORD);
	void setSizeBMP(DWORD);
	void setReserved1(WORD);
	void setReserved2(WORD);
	void setOffsetpixelarray(DWORD);
	void setSizebitmapinfoheader(DWORD);
	void setBitmapwidth(INT32);
	void setBitmapheight(INT32);
	void setColorplanes(WORD);
	void setColordepth(WORD);
	void setCompressionmethod(DWORD);
	void setRawimagesize(DWORD);
	void setHorizontalresolution(DWORD);
	void setVerticalresolution(DWORD);
	void setColorpallete(DWORD);
	void setImportantcolors(DWORD);
	WORD getFiletype();
	DWORD getSizeBMP();
	WORD getReserved1();
	WORD getReserved2();
	DWORD getOffsetpixelarray();
	DWORD getSizebitmapinfoheader();
	INT32 getBitmapwidth();
	INT32 getBitmapheight();
	WORD getColorplanes();
	WORD getColordepth();
	DWORD getCompressionmethod();
	DWORD getRawimagesize();
	DWORD getHorizontalresolution();
	DWORD getVerticalresolution();
	DWORD getColorpallete();
	DWORD getImportantcolors();

};

void BMPstructure::setFiletype(WORD Filetype)
{
	m_wFiletype = Filetype;
}
void BMPstructure::setSizeBMP(DWORD SizeBMP)
{
	m_dwSizeBMP = SizeBMP;
}
void BMPstructure::setReserved1(WORD Reserved1)
{
	m_wReserved1 = Reserved1;
}
void BMPstructure::setReserved2(WORD Reserved2)
{
	m_wReserved2 = Reserved2;
}
void BMPstructure::setOffsetpixelarray(DWORD Offsetpixelarray)
{
	m_dwOffsetpixelarray = Offsetpixelarray;
}
void BMPstructure::setSizebitmapinfoheader(DWORD Sizebitmapinfoheader)
{
	m_dwSizebitmapinfoheader = Sizebitmapinfoheader;
}
void BMPstructure::setBitmapwidth(INT32 Bitmapwidth)
{
	m_nBitmapwidth = Bitmapwidth;
}
void BMPstructure::setBitmapheight(INT32 Bitmapheight)
{
	m_nBitmapheight = Bitmapheight;
}
void BMPstructure::setColorplanes(WORD Colorplanes)
{
	m_wColorplanes = Colorplanes;
}
void BMPstructure::setColordepth(WORD Colordepth)
{
	m_wColordepth = Colordepth;
}
void BMPstructure::setCompressionmethod(DWORD Compressionmethod)
{
	m_dwCompressionmethod = Compressionmethod;
}
void BMPstructure::setRawimagesize(DWORD Rawimagesize)
{
	m_dwRawimagesize = Rawimagesize;
}
void BMPstructure::setHorizontalresolution(DWORD Horizontalresolution)
{
	m_dwHorizontalresolution = Horizontalresolution;
}
void BMPstructure::setVerticalresolution(DWORD Verticalresolution)
{
	m_dwVerticalresolution = Verticalresolution;
}
void BMPstructure::setColorpallete(DWORD Colorpallete)
{
	m_dwColorpallete = Colorpallete;
}
void BMPstructure::setImportantcolors(DWORD Importantcolors)
{
	m_dwImportantcolors = Importantcolors;
}
WORD BMPstructure::getFiletype()
{
	return m_wFiletype;
}
DWORD BMPstructure::getSizeBMP()
{
	return m_dwSizeBMP;
}
WORD BMPstructure::getReserved1()
{
	return m_wReserved1;
}
WORD BMPstructure::getReserved2()
{
	return m_wReserved2;
}
DWORD BMPstructure::getOffsetpixelarray()
{
	return m_dwOffsetpixelarray;
}

DWORD BMPstructure::getSizebitmapinfoheader()
{
	return m_dwSizebitmapinfoheader;
}
INT32 BMPstructure::getBitmapwidth()
{
	return m_nBitmapwidth;
}
INT32 BMPstructure::getBitmapheight()
{
	return m_nBitmapheight;
}
WORD BMPstructure::getColorplanes()
{
	return m_wColorplanes;
}
WORD BMPstructure::getColordepth()
{
	return m_wColordepth;
}
DWORD BMPstructure::getCompressionmethod()
{
	return m_dwCompressionmethod;
}
DWORD BMPstructure::getRawimagesize()
{
	return m_dwRawimagesize;
}
DWORD BMPstructure::getHorizontalresolution()
{
	return m_dwHorizontalresolution;
}
DWORD BMPstructure::getVerticalresolution()
{
	return m_dwVerticalresolution;
}
DWORD BMPstructure::getColorpallete()
{
	return m_dwColorpallete;
}
DWORD BMPstructure::getImportantcolors()
{
	return m_dwImportantcolors;
}
