#include "pch.h"
#include <iostream>
#include<Windows.h>
#include<cstdio>
#include"File.h"
int main()
{
	CFile obj;
	obj.create(L"F:\\Major_project.bmp",GENERIC_READ,FILE_SHARE_READ);
	return 0;
}

