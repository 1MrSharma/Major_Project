#pragma once
#include<Windows.h>
#include<vector>
using namespace std;

class CCmdLine
{
private:
	 vector<std::string> Optionslist;
	 string strCurrentOption;
public:
	BOOL Searchoptionslist(string);
	BOOL Checkextension(TCHAR*,const char[]);
	void Addoptions(string);
	void SetCurrentOption(string);
	string GetCurrentOption();
};


