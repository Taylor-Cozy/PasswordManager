#include <iostream>
#include "PassEncryptor.h"
#include "PasswordAnalyser.h"
#include "LoginManager.h"

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
	PasswordAnalyser pa("passwordtest.txt", true, &pe);

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
			break;
		case 4:
			break;
		}
	}
}
