#include "pch.h"
#include "Error.h"

DWORD CError::geterror(void)
{
	GetLastError();
}
