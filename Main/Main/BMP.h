#ifndef __BMP_H__
#define __BMP_H__
#include<Windows.h>

#include "BMPstructure.h"
class CBMP
{
private:
	BMPstructure *m_pStructurepointer;
public:
	void setStructurepointer(BMPstructure*);
	BOOL checkFiletype();
	DWORD returnSizeBMP();
	DWORD returnOffsetpixelarray();
	DWORD returnSizebitmapinfoheader();
	INT32 returnBitamapwidth();
	INT32 returnBitmapheight();
	WORD returnColorplanes();
	WORD returnColordepth();
	DWORD returnCompressionmethod();
	DWORD returnRawimagesize();
	DWORD returnHorizontalresolution();
	DWORD returnVerticalresolution();
	DWORD returnColorpallete();
	DWORD returnImportantcolors();
};

#endif
