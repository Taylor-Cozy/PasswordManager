#include "PasswordAnalyserManager.h"


PasswordAnalyserManager::PasswordAnalyserManager(string filepath, bool overwrite, PassEncryptor* pe) : PasswordAnalyser(filepath, overwrite, pe)
{
}

PasswordAnalyserManager::~PasswordAnalyserManager()
{
}

void PasswordAnalyserManager::PrintMenu()
{
	cout << "\nPassword Cracker Menu: " << endl;
	cout << "1. Brute Force (Very Slow)\n"
		<< "2. Calculate Number of Possible Passwords (Slow)\n"
		<< "3. Test Passwords\n"
		<< "4. Restrict Range\n"
		<< "\n0. Exit"
		<< "\n> ";
}

void PasswordAnalyserManager::Menu()
{
	params p;

	auto getParams = [&p]() {
		while (true) {
			cout << "Which set would you like to use?\nSet 1 - 10 Chars, Repeated.\nSet 2 - Non Repeated, Extended ASCII set.\n>";
			cin >> p.set;

			if (p.set == 1 || p.set == 2)
				break;
			else
				cout << "Invalid input, please try again." << endl;
		}

		while (true) {
			
			cout << "Please input starting char length\n> ";
			cin >> p.start;

			cout << "Please input finishing char length\n>";
			cin >> p.end;

			if (p.end >= p.start && p.start >= 1 && p.end <= 100)
				break;
			else
				cout << "Invalid input, please try again." << endl;
		}
	};

	int option = -1;
	while (option != 0) {
		PrintMenu();
		cin >> option;

		switch (option) {
		case 1:
			getParams();
			TestBruteForce(p);
			break;
		case 2:
			getParams();
			TestCombinatorialStrength(p);
			break;
		case 3:
			void (*foo)(params);
			//foo = TestDecrypt;
			// TODO Fix
			getParams();
			TestMethod(foo, p);
			break;
		case 4:
			break;
		}
	}
}



void PasswordAnalyserManager::TestBruteForce(params p)
{

}

void PasswordAnalyserManager::TestDecrypt(params p)
{

	for (int i = p.start; i <= p.end; i++) {
		double categoryAverage = 0;
		for (int j = 0; j < 100; j++) {
			string password = *passwords[(10000 * (p.set - 1)) + ((i - 1) * 100) + j];
			auto t1 = chrono::high_resolution_clock::now();
			Decrypt(password);
			auto t2 = chrono::high_resolution_clock::now();

			chrono::duration<double, std::milli> millis = t2 - t1;
			categoryAverage += millis.count();
			//cout << ((i-1) * 100) + j + 1 << ": " << millis.count() << "ms" << endl;
		}

		cout << "Average for " << i << " chars: " << categoryAverage / 100.0 << "ms" << endl;
	}
}

void PasswordAnalyserManager::TestCombinatorialStrength(params p)
{
}

// TODO: Template that takes 