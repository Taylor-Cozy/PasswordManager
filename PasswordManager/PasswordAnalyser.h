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

	void BruteForce(vector<vector<int>>& decryptedPasswords, vector<int>& decrypted, string remaining, int offset = 0);

	bool DecryptPassword(vector<int>& decrypted, string remaining, int offset = 0);

	void SmartDecrypt(string password);
	void Decrypt(string password);

	void GenerateViablePaths(vector<vector<int>>& vectorVector, vector<int>& test, string password, int offset = 0);
	void CalculateNumberPasswords(vector<vector<int>>& combinations);

	string getPassword(int index) {
		return *(passwords[index]);
	};

private:
	string** passwords;
	PassEncryptor* pe;
	set<int> validChars;
	int lowerBound = 1;
	int upperBound = 256;
};