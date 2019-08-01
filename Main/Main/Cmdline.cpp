#include "pch.h"
#include"CmdLine.h"
#include<regex>
#include<string>
#include<vector>
using namespace std;

void CCmdLine::Addoptions(string strOption)
{
	Optionslist.push_back(strOption);
}
BOOL CCmdLine::Searchoptionslist(string strOption)
{
	if (std::find(Optionslist.begin(), Optionslist.end(), strOption) != Optionslist.end() == TRUE)
	{
		SetCurrentOption(strOption);
		return TRUE;
	}
	return FALSE;
}
BOOL CCmdLine::Checkextension(TCHAR* arg,const char str[])
{
	string objPhrase = arg;
	smatch objMatch;
	regex expr(str);
	return (std::regex_search(objPhrase, objMatch, expr));
}
void CCmdLine::SetCountargument(int nCountargumentemp)
{
	nCountargument = nCountargumentemp;
}
void CCmdLine::SetCurrentOption(string strOption)
{
	strCurrentOption = strOption;
}
int CCmdLine::GetCountargument()
{
	return nCountargument;
}
string CCmdLine::GetCurrentOption()
{
	return strCurrentOption;
}