#include "pch.h"
#include "BMP.h"



void CBMP::fnsetStructurepointer(BMPstructure* Structurepointer)
{
	m_pStructurepointer = Structurepointer;
}


BOOL CBMP::fncheckFiletype()
{
	return m_pStructurepointer->fngetFiletype() == 0x4D42;
}

DWORD CBMP::fnreturnSizeBMP()
{
	return m_pStructurepointer->fngetSizeBMP();
}

DWORD CBMP::fnreturnOffsetpixelarray()
{
	return m_pStructurepointer->fngetOffsetpixelarray();
}

DWORD CBMP::fnreturnSizebitmapinfoheader()
{
	return m_pStructurepointer->fngetSizebitmapinfoheader();
}
INT32 CBMP::fnreturnBitamapwidth()
{
	return m_pStructurepointer->fngetBitmapwidth();
}
INT32 CBMP::fnreturnBitmapheight()
{
	return m_pStructurepointer->fngetBitmapheight();
}
WORD CBMP::fnreturnColorplanes()
{
	return m_pStructurepointer->fngetColorplanes();
}
WORD CBMP::fnreturnColordepth()
{
	return m_pStructurepointer->fngetColordepth();
}
DWORD CBMP::fnreturnCompressionmethod()
{
	return m_pStructurepointer->fngetCompressionmethod();
}
DWORD CBMP::fnreturnRawimagesize()
{
	return m_pStructurepointer->fngetRawimagesize();
}
DWORD CBMP::fnreturnHorizontalresolution()
{
	return m_pStructurepointer->fngetHorizontalresolution();
}
DWORD CBMP::fnreturnVerticalresolution()
{
	return m_pStructurepointer->fngetVerticalresolution();
}
DWORD CBMP::fnreturnColorpallete()
{
	return m_pStructurepointer->fngetColorpalette();
}
DWORD CBMP::fnreturnImportantcolors()
{
	return m_pStructurepointer->fngetImportantcolors();
}
