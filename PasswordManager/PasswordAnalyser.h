#pragma once
#include "PassAnalyserError.h"
#include "FileHandler.h"
#include "PassEncryptor.h"

using namespace std;

class PasswordAnalyser : public FileHandler{
public:
	PasswordAnalyser(string, bool, PassEncryptor*);
	~PasswordAnalyser();

	void GeneratePasswords();

	string GenerateRepetitivePass(int length);
	string GenerateNonRepetitivePass(int length);

private:
	string* passwords;
	PassEncryptor* pe;
};