#pragma once
#include <string>

using namespace std;

class PassEncryptor {
public:
	string EncryptPass(string passPlain) const;
	int CollatzConjecture(int n, int count = 0) const;
};