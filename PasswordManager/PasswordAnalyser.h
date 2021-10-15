#pragma once
#include "PassAnalyserError.h"
#include "FileHandler.h"
#include "PassEncryptor.h"
#include <vector>
#include <time.h>
#include <set>
#include <stdlib.h>
#include <algorithm>

using namespace std;

class PasswordAnalyser : public FileHandler{
public:
	PasswordAnalyser(string, bool, PassEncryptor*);
	~PasswordAnalyser();

	void ReadInPasswords();

	void GeneratePasswords();
	void ClearFile();
	void PrintPasswords();

	string* GenerateRepetitivePass(int length);
	string* GenerateNonRepetitivePass(int length);

private:
	string** passwords;
	PassEncryptor* pe;
	set<int> validChars;
};