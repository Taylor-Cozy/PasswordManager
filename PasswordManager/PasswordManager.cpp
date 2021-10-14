#include <iostream>
#include "PassEncryptor.h"
#include "LoginManager.h"

using namespace std;

LoginManager lm("passwords.txt");
PassEncryptor pe;

void printMenu() {
	cout << "\n\nPlease pick an option from the following:" << endl;
	cout << "1. Create username and password\n"
		<< "2. Check username and password\n"
		<< "3. Generate password strength analysis file\n"
		<< "4. Analyse password strength analysis file\n"
		<< "\n0. Exit" 
		<< "\n> ";
};

void getLogin(login& l) {
	cout << "Enter username: ";
	cin >> l.username;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Enter password: ";
	string plainPass;
	cin >> plainPass;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	l.passHash = pe.EncryptPass(plainPass);
}

void attemptLogin(login& l) {
	int tries = 3;

	while (tries > 0) {
		cout << tries << " remaining.\n";
		getLogin(l);
		if (lm.CheckFile(l)) {
			cout << "Successfully logged in.\n";
			return;
		}
		cout << "Username or Password incorrect.\n";
		tries--;
	}

	cout << "Ran out of tries.\n";
}

int main()
{

	int option = -1;
	login log;

	while (option != 0) {
		printMenu();
		cin >> option;

		switch (option) {
		case 1:
			getLogin(log);
			cout << lm.AddLogin(log);
			break;
		case 2:
			attemptLogin(log);
			break;
		case 3:
			break;
		case 4:
			break;
		}
	}
}
