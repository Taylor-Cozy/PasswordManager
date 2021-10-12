#pragma once
#include <string>
#include <fstream>

using namespace std;

struct login {
	string username;
	string passHash;
};

class FileHandler {
public:
	FileHandler(string filepath);
	~FileHandler();
	void checkFile();
	void writeFile(login l);
private:
	fstream passFile;
};