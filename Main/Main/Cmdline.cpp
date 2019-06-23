#include "pch.h"
#include"CmdLine.h"
#include<regex>
#include<string>
#include<vector>
using namespace std;
BOOL CCmdLine::fnCheckOptionList(TCHAR* arg3)
{
	std::vector<std::string> vect{ "-h1", "-h2", "-i", "-p", "-o", "-bw" };
	return std::find(vect.begin(), vect.end(), arg3) != vect.end();
}
BOOL CCmdLine::fnCheckEndingCharofBMP(TCHAR* arg)
{
	std::string objPhrase = arg;
	std::smatch objMatch;
	std::regex expr("^[a-zA-Z0-9]:\.*.bmp$");
	return (std::regex_search(objPhrase, objMatch, expr));
}
