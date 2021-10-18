#include <iostream>
#include "PassEncryptor.h"
#include "PasswordAnalyser.h"
#include "LoginManager.h"
#include <vector>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <chrono>

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

	//"20953985" 27322810313331033910211452912207344136146925461033281533271031012815108114101

	string password = "2511683441528231082628281161141141272146671111012628769674410388441031141312113341528234615203315282846232320152090441533908844234611611411434152811621334115201515332395114131211142110311439101133428108882610852152020203341";

	auto t1 = chrono::high_resolution_clock::now();
	pa.SmartDecrypt(password);
	auto t2 = chrono::high_resolution_clock::now();

	chrono::duration<double, std::milli> ms_double = t2 - t1;
	cout << ms_double.count() << "ms\n";

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
			pa.GeneratePasswords();
			break;
		case 4:
			break;
		}
	}
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