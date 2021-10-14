#include "PasswordAnalyser.h"

PasswordAnalyser::PasswordAnalyser(string filepath, bool overwrite, PassEncryptor* pe) : FileHandler(filepath, overwrite), pe(pe)
{
	passwords = new string[20000];
}

PasswordAnalyser::~PasswordAnalyser()
{
	delete[] passwords;
	passwords = nullptr;
	pe = nullptr;
}

void PasswordAnalyser::GeneratePasswords()
{
	int length;

	for (int i = 0; i < 10000; i++) {
		length = i % 100;
		passwords[i] = GenerateRepetitivePass(length);
		passwords[10000 + i] = GenerateNonRepetitivePass(length);
	}

	// TODO: Iterate over array on heap, adding each to the file.
}

string PasswordAnalyser::GenerateRepetitivePass(int length)
{
	// TODO
	return string();
}

string PasswordAnalyser::GenerateNonRepetitivePass(int length)
{
	// TODO
	return string();
}
