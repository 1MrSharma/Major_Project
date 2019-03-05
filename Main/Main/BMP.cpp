#include "pch.h"
#include "BMP.h"



void CBMP::setStructurepointer(BMPstructure* Structurepointer)
{
	m_pStructurepointer = Structurepointer;
}


BOOL CBMP::checkFiletype()
{
	return m_pStructurepointer->getFiletype() == 0x4D42;
}

DWORD CBMP::returnSizeBMP()
{
	return m_pStructurepointer->getSizeBMP();
}

DWORD CBMP::returnOffsetpixelarray()
{
	return m_pStructurepointer->getOffsetpixelarray();
}

DWORD CBMP::returnSizebitmapinfoheader()
{
	return m_pStructurepointer->getSizebitmapinfoheader();
}
INT32 CBMP::returnBitamapwidth()
{
	return m_pStructurepointer->getBitmapwidth();
}
INT32 CBMP::returnBitmapheight()
{
	return m_pStructurepointer->getBitmapheight();
}
WORD CBMP::returnColorplanes()
{
	return m_pStructurepointer->getColorplanes();
}
WORD CBMP::returnColordepth()
{
	return m_pStructurepointer->getColordepth();
}
DWORD CBMP::returnCompressionmethod()
{
	return m_pStructurepointer->getCompressionmethod();
}
DWORD CBMP::returnRawimagesize()
{
	return m_pStructurepointer->getRawimagesize();
}
DWORD CBMP::returnHorizontalresolution()
{
	return m_pStructurepointer->getHorizontalresolution();
}
DWORD CBMP::returnVerticalresolution()
{
	return m_pStructurepointer->getVerticalresolution();
}
DWORD CBMP::returnColorpallete()
{
	return m_pStructurepointer->getColorpallete();
}
DWORD CBMP::returnImportantcolors()
{
	return m_pStructurepointer->getImportantcolors();
}
