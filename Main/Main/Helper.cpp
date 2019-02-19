#include "pch.h"
#include "Helper.h"
#include<Windows.h>
#include<stdlib.h>
WORD CHelper::circularbyteshift(WORD  wBytes)//, DWORD dwSize,BYTE nTimes)
{
	
	WORD t=wBytes >> 8;
	return t;
}
/*
 * Right shift 8 times
 * 0 1 0 0    1 1 0 1    0 1 0 0    0 0 1 0->4D42
 * 0 0 1 0    0 1 1 0    1 0 1 0    0 0 0 1
 * 1 0 0 1    0 0 1 1    0 1 0 1    0 0 0 0
 * 0 1 0 0    1 0 0 1    1 0 1 0    1 0 0 0
 * 0 0 1 0    0 1 0 0    1 1 0 1    0 1 0 0
 * 0 0 0 0    0 0 1 0    0 1 1 0    1 0 1 0
 * 0 0 0 0    1 0 0 1    0 0 1 1    0 1 0 1
 * 1 0 0 0    0 1 0 0    1 0 0 1    1 0 1 0
 * 0 1 0 0    0 0 1 0    0 1 0 0    1 1 0 1->424D
 */

//323D43--> 433D32 6
//4D42--> 424D -2