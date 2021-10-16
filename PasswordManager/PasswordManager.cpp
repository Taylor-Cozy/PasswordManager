#include <iostream>
#include "PassEncryptor.h"
#include "PasswordAnalyser.h"
#include "LoginManager.h"
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>

using namespace std;

void printMenu() {
	cout << "\n\nPlease pick an option from the following:" << endl;
	cout << "1. Create username and password\n"
		<< "2. Check username and password\n"
		<< "3. Generate password strength analysis file\n"
		<< "4. Analyse password strength analysis file\n"
		<< "\n0. Exit" 
		<< "\n> ";
};

int main()
{
	PassEncryptor pe;
	LoginManager lm("passwords.txt", false, &pe);
	PasswordAnalyser pa("passwordtest.txt", false, &pe);

	// 1 - 255
	// 20
	int passCount = 0;
	int count = 0;
	vector<int> decrypt;
	vector<vector<int>> possibilities;

	//for (int i = 0; i < 500; i++) {
	//	cout << "Password " << i << ": " << pa.getPassword(i) << endl;
	//	count++;
	//	decrypt.clear();
	//	possibilities.clear();
	//	pa.DecryptPassword(possibilities, decrypt, pa.getPassword(i));
	//	passCount += possibilities.size();
	//}

	//cout << "Average Number of Passwords: " << (passCount * 1.0f) / (count * 1.0f) << endl;
	//string x;
	//cout << "Press any key to start: ";
	//cin >> x;
	//pa.DecryptPassword(possibilities, decrypt, "20953985");
	//
	//for (auto x : possibilities) {
	//	for (auto i : x) {
	//		cout << char(i);
	//	} cout << endl;
	//}
	
	//int offset = 0;

	//for (int i = 32; i < 127; i++) {
	//	cout << char(i) << " : " << pe.CollatzConjecture(i + offset) << endl;
	//}

	//cout << "==============================" << endl;
	//cout << endl;

	//unordered_map<int, vector<int>> possible;
	//vector<int> test;
	//test.emplace_back(0);
	//possible.insert(pair<int, vector<int>>(1, test));
	//possible.insert(pair<int, vector<int>>(0, test));
	//possible.insert(pair<int, vector<int>>(4, test));
	//possible.insert(pair<int, vector<int>>(5, test));

	//for (auto m : possible) {
	//	cout << m.first << endl;
	//}

	//vector<string> test;
	//test.emplace_back("pelt");
	//test.emplace_back("pert");
	//test.emplace_back("pest");
	//test.emplace_back("pett");
	//test.emplace_back("telt");
	//test.emplace_back("tert");
	//test.emplace_back("test");
	//test.emplace_back("tett");
	//test.emplace_back("uelt");
	//test.emplace_back("uert");
	//test.emplace_back("uest");
	//test.emplace_back("uett");
	//test.emplace_back("xelt");
	//test.emplace_back("xert");
	//test.emplace_back("xest");
	//test.emplace_back("xett");
	//test.emplace_back("zelt");
	//test.emplace_back("zert");
	//test.emplace_back("zest");
	//test.emplace_back("zett");

	//login l;
	//l.username = "ThisIsATest";

	//int count = 0;
	//int total = 0;

	//for (string x : test) {
	//	l.password = pe.EncryptPass(x);
	//	if (lm.CheckFile(l))
	//		count++;
	//	total++;
	//}

	//cout << count << " of " << total << " correct." << endl;

	//login log;

	//int option = -1;

	//while (option != 0) {
	//	printMenu();
	//	cin >> option;

	//	switch (option) {
	//	case 1:
	//		lm.genLogin(log);
	//		cout << lm.AddLogin(log);
	//		break;
	//	case 2:
	//		cout << (lm.AttemptLogin(log) ? "Success" : "Failure") << endl;
	//		break;
	//	case 3:
	//		pa.GeneratePasswords();
	//		break;
	//	case 4:
	//		break;
	//	}
	//}
}



//for (int i = 0; i < 10000; i++) {
//	cout << i << " : " << (i / 100) + 1 << "\t\t\t\t" << 10000 + i << " : " << (i / 100) + 1 << endl;
//}

//pa.ReadInPasswords();
//pa.PrintPasswords();

//set<int> validChars;

//int i = 0;
//while (validChars.size() < 10) {
//	i++;
//	int x = rand() % 26 + 97;
//	validChars.insert(x);
//	cout << i << ": " << x << endl;
//}
//cout << "Finished Set: [";
//for (auto i : validChars) {
//	cout << " " << i;
//}
//cout << " ]" << endl;

//cout << "Finished Set: [";
//for (auto i : validChars) {
//	char x = i;
//	cout << " " << x;
//}
//cout << " ]" << endl;