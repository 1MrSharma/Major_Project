#pragma once
#include<Windows.h>
#include<vector>
using namespace std;

class CCmdLine
{
private:
	 vector<std::string> Vect;
	 string strCurrentOption;
public:
	void fnCreateVector(string);
	BOOL fnCheckVector(string);
	BOOL fnCheckFILE(TCHAR*,char[]);
	void fnSetCurrentOption(string);
	string fnGetCurrentOption();
};

/*
* Usage: <Source> <Destination> <options> { Source bitmap file and either of one option is required out of three }
 * -h1 : Show bitmap file header : <Source.bmp> <-h1>
 * -h2 : Show DIB header         : <Source.bmp> <-h2>      
 ** -i  : Basic information of .bmp image file      : <Source.bmp> <-i>
 * -p  : Show pixel array        : <Source.bmp> <Destination.bmp> <-p>
 ** -o  : Original image copy     : <Source.bmp> <Destination.bmp> <-o>
 ** -bw : Black and White image   : <Source.bmp> <Destination.bmp> <-bw>
 */
