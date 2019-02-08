#include "pch.h"
#include "Helper.h"
#include<Windows.h>
WORD CHelper::circularbyteshift(PWORD pointer_to_MN, DWORD size_of_last_field)
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