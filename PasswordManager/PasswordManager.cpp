#include <iostream>
#include "PassEncryptor.h"
#include "PasswordAnalyser.h"
#include "PasswordAnalyserManager.h"
#include "LoginManager.h"
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <chrono>

using namespace std;

// TODO: Setup Menu properly (including password analyser)
// TODO: Create Password Analyser Manager that shows analytics
// TODO: Triple Check against mark scheme
// TODO: Refactor / Clean up code
// TODO: Fully decrypt sentence

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
	PasswordAnalyserManager pm("passwordtest.txt", false, &pe);

	//vector<int> left, right;
	//left.emplace_back(1);
	//right.emplace_back(2);
	//right.emplace_back(2);

	//pm.AddBigInteger(left, right);

	login log;
	int option = -1;

	while (option != 0) {
		printMenu();
		cin >> option;

		switch (option) {
		case 1:
			lm.genLogin(log);
			cout << lm.AddLogin(log);
			break;
		case 2:
			cout << (lm.AttemptLogin(log) ? "Success" : "Failure") << endl;
			break;
		case 3:
			pm.GeneratePasswords();
			break;
		case 4:
			pm.Menu();
			break;
		}
	}
}