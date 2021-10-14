#pragma once
#include <string>
#include <fstream>
#include <map>
#include <stdexcept>
using namespace std;

class FileHandler {
public:
	FileHandler(string) throw (invalid_argument);
	~FileHandler();
	void WriteFile(string);

protected:
	
	fstream passFile;
	map<string, string> logins;
};