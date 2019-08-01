#pragma once
#include<Windows.h>
#include<vector>
using namespace std;

class CCmdLine
{
private:
	 vector<std::string> Optionslist;
	 string strCurrentOption;
	 int nCountargument;
public:
	BOOL Searchoptionslist(string);
	BOOL Checkextension(TCHAR*, char[]);
	void Addoptions(string);
	void SetCurrentOption(string);
	void SetCountargument(int);
	int GetCountargument();
	string GetCurrentOption();
};


