#include <iostream>
#include "FileHandler.h"

using namespace std;

void printMenu() {
	cout << "Please pick an option from the following:" << endl;
	cout << "1. Create username and password\n"
		<< "2. Check username and password\n"
		<< "3. Generate password strength analysis file\n"
		<< "4. Analyse password strength analysis file\n"
		<< "5. Exit" << endl;
};

int main()
{
	FileHandler fh("passwords.txt");

	printMenu();
	int option;
	cin >> option;

	switch (option) {
	case 1:
		cout << "Ok boss" << endl;
		fh.writeFile();
		fh.checkFile();
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	}
		
}
