#pragma once
#include<Windows.h>
class CBMP
{
private:
	WORD m_dwFiletype;//00 (2 bytes)--As word is 2 byte
	DWORD m_dwBitmapwidthpixel;//12 (4 bytes)
	DWORD m_dwBitmapheightpixel;//16 (4 bytes)
	WORD m_dwColorplanes;//1A (2 bytes)
	WORD m_dwBitsperpixel;//1C (2 bytes)
	LPCTSTR m_szCompressionmethod;//1E (4 bytes)
	DWORD m_dwHorizontalresolution;//26 (4 bytes)
	DWORD m_dwVerticalresolution;//starting 2A (4 bytes)
	DWORD m_dwColorpalette;//starting 2E (4 bytes)
};

