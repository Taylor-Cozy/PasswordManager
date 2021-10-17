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

	void DecryptPassword(vector<vector<int>>& decryptedPasswords, vector<int>& decrypted, string remaining, int offset = 0);

	void SmartDecrypt(map<int, set<int>>& possibilities, string password, int offset = 0);
	//void LetterPlacement(vector<vector<int>>& letters, vector<int>& letterPlacement, map<int, set<int>> possibilities, string password, int offset = 0);
	//void Letter_Placement(vector<int>& letterPlacement, map<int, set<int>> possibilities, string reversedPassword, int key = -1);
	void LetterPlacement(set<vector<int>>& combinations, vector<int>& letterPlacement, map<int, set<int>> possibilities, string password, int maxSize, int previousSize = 1);

	string getPassword(int index) {
		return *(passwords[index]);
	};

private:
	string** passwords;
	PassEncryptor* pe;
	set<int> validChars;
};