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
	virtual ~PasswordAnalyser();

	void ReadInPasswords();

	void GeneratePasswords();
	void ClearFile();
	void PrintPasswords();

	string* GenerateRepetitivePass(int length);
	string* GenerateNonRepetitivePass(int length);

	void GetAllPasswords(string password);
	void BruteForce(vector<vector<int>>& decryptedPasswords, vector<int>& decrypted, string remaining, int offset = 0);
	
	void DecryptPassword(vector<int>& decrypted);
	bool GenerateFirstViablePath(vector<int>& decrypted, string remaining, int offset = 0);

	bool SmartDecrypt(string password);
	bool Decrypt(string password);

	void GenerateViablePaths(vector<vector<int>>& viablePaths, vector<int>& path, string password, int offset = 0);
	void CalculateNumberPasswords(vector<vector<int>>& combinations);

	void MultiplyBigInteger(vector<int>& bigInteger, int mult);
	void AddBigInteger(vector<int>& left, vector<int> right);

	string getPassword(int index) {
		return *(passwords[index]);
	};

protected:
	string** passwords;
	PassEncryptor* pe;
	set<int> validChars;
	int lowerBound = 1;
	int upperBound = 256;
};