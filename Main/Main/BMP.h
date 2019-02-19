#pragma once
#include<Windows.h>
class CBMP
{
private:
	BYTE * pbStructurepointer;
public:
	void setStructurepointer(BYTE);
	BOOL checkFiletype(WORD);
	DWORD returnSizeBMP(DWORD);
	DWORD returnOffsetpixelarray(DWORD);
	DWORD returnSizebitmapinfoheader(DWORD);
	INT32 returnBitamapwidth(INT32);
	INT32 returnBitmapheight(INT32);
	WORD returnColorplanes(WORD);
	WORD returnColordepth(WORD);
	DWORD returnCompressionmethod();
	DWORD returnRawimagesize(DWORD);
	DWORD returnHorizontalresolution(DWORD);
	DWORD returnVerticalresolution(DWORD);
	DWORD returnColorpallete(DWORD);
	DWORD returnImportantcolors(DWORD);
};

