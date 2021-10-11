#pragma once
#include <string>
#include <fstream>

using namespace std;

struct login {
	string username;
	string passPlain;
	//int passHash;
};

class FileHandler {
public:
	FileHandler(string filepath);
	~FileHandler();
	void checkFile();
	void writeFile();
private:
	fstream passFile;
};