#ifndef __BMP_H__
#define __BMP_H__
#include<Windows.h>

#include "BMPstructure.h"
class CBMP
{
private:
	BMPstructure *m_pStructurepointer;
public:
	void fnsetStructurepointer(BMPstructure*);
	BOOL fncheckFiletype();
	WORD fnreturnFiletype();
	WORD fnreturnReserved1();
	WORD fnreturnReserved2();
	DWORD fnreturnSizeBMP();
	DWORD fnreturnOffsetpixelarray();
	DWORD fnreturnSizebitmapinfoheader();
	INT32 fnreturnBitamapwidth();
	INT32 fnreturnBitmapheight();
	WORD fnreturnColorplanes();
	WORD fnreturnColordepth();
	DWORD fnreturnCompressionmethod();
	DWORD fnreturnRawimagesize();
	DWORD fnreturnHorizontalresolution();
	DWORD fnreturnVerticalresolution();
	DWORD fnreturnColorpallete();
	DWORD fnreturnImportantcolors();
};

#endif
