#pragma once
#include "PassAnalyserError.h"
#include "FileHandler.h"

using namespace std;

class PasswordAnalyser : public FileHandler{
public:
	PasswordAnalyser(string);
	~PasswordAnalyser();

	void GeneratePasswords();
private:
	string passwords[20000];
};