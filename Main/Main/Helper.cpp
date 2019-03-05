#include "pch.h"
#include "Helper.h"
#include<Windows.h>
#include<stdlib.h>
WORD CHelper::circularbyteshift(WORD  wBytes)
{
	
	WORD t=wBytes >> 8;
	return t;
}
