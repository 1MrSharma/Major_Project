#include "pch.h"
#include "Error.h"

CHAR CError::geterror(void)
{
	m_szErrName=GetLastError();
	return m_szErrName;
}
