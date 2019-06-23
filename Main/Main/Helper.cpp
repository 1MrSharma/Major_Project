#include "pch.h"
#include "Helper.h"
#include<Windows.h>
#include<stdlib.h>
int CHelper::fnChangeEndianess(int nValue)
{
	int nRetval;
	nRetval = nValue & 0xFF;
	nRetval = (nRetval << 8) | ((nValue >> 8) & 0xFF);
	nRetval = (nRetval << 8) | ((nValue >> 16) & 0xFF);
	nRetval = (nRetval << 8) | ((nValue >> 24) & 0xFF);
	return nRetval;
}
int CHelper::fnExtraBitmask(int nValue)
{
	return 0;
}
WORD CHelper::fnDecimalToHexadecimal()
{
	return 0;
}