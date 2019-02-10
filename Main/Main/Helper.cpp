#include "pch.h"
#include "Helper.h"
#include<Windows.h>
WORD CHelper::circularbyteshift(PWORD pBytes, DWORD dwSize,BYTE nTimes)
{
	return ' ';
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