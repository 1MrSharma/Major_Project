#pragma once
#include<Windows.h>
#include"BMPstructure.h"
class CBMP
{
private:
	DWORD64 * pbStructurepointer;
public:
	void setStructurepointer(BMPstructure* );
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

