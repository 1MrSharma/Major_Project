#include "pch.h"
#include "BMP.h"
#include"BMPstructure.h"

void CBMP::setStructurepointer(BMPstructure* Structurepointer)
{
	* pbStructurepointer = Structurepointer;///PROBLEM 1
}
