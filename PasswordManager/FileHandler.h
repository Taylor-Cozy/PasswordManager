#pragma once
#include <string>
#include <fstream>
#include <map>
#include <iostream>
#include <stdexcept>
using namespace std;

class FileHandler {
public:
	FileHandler(string, bool) throw (invalid_argument);
	~FileHandler();
	void WriteFile(string);

protected:
	string filepath;
	fstream passFile;
	map<string, string> logins;
};