#include <iostream>
#include "FileHandler.h"

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



int CollatzConjecture(int n, int count = 0) {
	if (n == 1)
		return count;

	count++;
	n % 2 == 0 ? CollatzConjecture(n / 2, count) : CollatzConjecture(3 * n + 1, count);
}

string EncryptPassword(string passPlain) {
	
	int offset = 0;
	string password = "";

	for (char c : passPlain) {
		offset = CollatzConjecture(c + offset);
		password += to_string(offset);
	}

	return (password);
}

void getLogin(login& l) {
	cout << "Enter username: ";
	cin >> l.username;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	cout << "Enter password: ";
	string passPlain;
	cin >> passPlain;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	l.passHash = EncryptPassword(passPlain);
}

int main()
{
	FileHandler fh("passwords.txt");

	int option = -1;
	login log;

	while (option != 0) {
		printMenu();
		cin >> option;

		switch (option) {
		case 1:
			getLogin(log);
			fh.writeFile(log);
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		}
	}
}
