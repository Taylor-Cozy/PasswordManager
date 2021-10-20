#pragma once
#include "PasswordAnalyser.h"
#include <chrono>

struct params {
	int start, end, set;
};

typedef bool (PasswordAnalyser::* decryptMethodPtr)(string);

class PasswordAnalyserManager : public PasswordAnalyser {
public:
	PasswordAnalyserManager(string filepath, bool overwrite, PassEncryptor* pe);
	virtual ~PasswordAnalyserManager();
	
	void PrintMenu();
	void Menu();

	void TestBruteForce(params p);
	void TestDecrypt(params p);
	void TestCombinatorialStrength(params p);

	void TestMethod(decryptMethodPtr t, params p);
	void test(string print);

};
