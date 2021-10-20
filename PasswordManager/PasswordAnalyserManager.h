#pragma once
#include "PasswordAnalyser.h"
#include <chrono>

struct params {
	int start, end, set;
};

class PasswordAnalyserManager : public PasswordAnalyser {
public:
	PasswordAnalyserManager(string filepath, bool overwrite, PassEncryptor* pe);
	virtual ~PasswordAnalyserManager();
	
	void PrintMenu();
	void Menu();

	void TestBruteForce(params p);
	void TestDecrypt(params p);
	void TestCombinatorialStrength(params p);

	template <typename T>
	void TestMethod(T t, params p);
};

template<typename T>
inline void PasswordAnalyserManager::TestMethod(T t, params p)
{
	for (int i = p.start; i <= p.end; i++) {
		double categoryAverage = 0;
		for (int j = 0; j < 100; j++) {
			string password = *passwords[(10000 * (p.set - 1)) + ((i - 1) * 100) + j];
			auto t1 = chrono::high_resolution_clock::now();
			t(password);
			auto t2 = chrono::high_resolution_clock::now();

			chrono::duration<double, std::milli> millis = t2 - t1;
			categoryAverage += millis.count();
			//cout << ((i-1) * 100) + j + 1 << ": " << millis.count() << "ms" << endl;
		}

		cout << "Average for " << i << " chars: " << categoryAverage / 100.0 << "ms" << endl;
	}
}
