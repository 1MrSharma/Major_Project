#include "pch.h"
#include"CmdLine.h"
#include<regex>
#include<string>
#include<vector>
using namespace std;

void CCmdLine::fnCreateVector(string B)
{
	Vect.push_back(B);
}
BOOL CCmdLine::fnCheckVector(string A)
{
	if (std::find(Vect.begin(), Vect.end(), A) != Vect.end() == TRUE)
	{
		fnSetCurrentOption(A);
		return TRUE;
	}
	return FALSE;
}
BOOL CCmdLine::fnCheckFILE(TCHAR* arg,char str[])
{
	char a[] = "$";
	strcat_s(str,sizeof str, a);
	string objPhrase = arg;
	smatch objMatch;
	regex expr(str);
	return (std::regex_search(objPhrase, objMatch, expr));
}
void CCmdLine::fnSetCurrentOption(string str)
{
	strCurrentOption = str;
}
string CCmdLine::fnGetCurrentOption()
{
	return strCurrentOption;
}