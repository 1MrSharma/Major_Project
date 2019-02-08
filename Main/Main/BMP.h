#pragma once
#include<Windows.h>
class CBMP
{
private:
	WORD m_wFiletype;	
	DWORD m_dwBitmapwidthpixel;
	DWORD m_dwBitmapheightpixel;
	WORD m_wColorplanes;
	WORD m_wColordepth;
	DWORD m_dwCompressionmethod[4];
	DWORD m_dwHorizontalresolution;
	DWORD m_dwVerticalresolution;
	DWORD m_dwColorpalette;
};

