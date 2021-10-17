#include "PasswordAnalyser.h"

PasswordAnalyser::PasswordAnalyser(string filepath, bool overwrite, PassEncryptor* pe) : FileHandler(filepath, overwrite), pe(pe)
{
	passwords = new string* [20000]{nullptr}; // non contiguous
	
	passwords[0] = new string[50];

	srand(time(NULL));

	while (validChars.size() < 10) {
		int x = rand() % 26 + 97;
		validChars.insert(x);
	}
	
	if (!overwrite) {
		ReadInPasswords();
	}
}

PasswordAnalyser::~PasswordAnalyser()
{
	for (int i = 0; i < 20000; i++) {
		if(passwords[i])
			delete passwords[i];
	}
	delete[] passwords;
	passwords = nullptr;
	pe = nullptr;
}

void PasswordAnalyser::ReadInPasswords()
{
	string pass;
	string* x;
	int i = 0;
	passFile.clear();
	passFile.seekg(ios::beg);
	while (getline(passFile, pass)) {
		x = new string();
		*x = pass;
		passwords[i] = x;
		i++;
		x = nullptr;
	}
	cout << i << endl;
}

void PasswordAnalyser::PrintPasswords() {
	for (int i = 0; i < 20000; i++) {
		if(passwords[i])
			cout << *(passwords[i]) << endl;
	}
}

void PasswordAnalyser::GeneratePasswords()
{
	passFile.clear();
	passFile.seekg(ios::beg);
	if (!(passFile.peek() == std::fstream::traits_type::eof())) {
		ClearFile();
	}
	
	int length;

	for (int i = 0; i < 10000; i++) {
		length = (i / 100) + 1;
		passwords[i] = GenerateRepetitivePass(length);
		passwords[10000 + i] = GenerateNonRepetitivePass(length);
	}

	for (int i = 0; i < 20000; i++) {
		if (passwords[i])
			passFile << *passwords[i] << "\n";
	}
}

void PasswordAnalyser::ClearFile()
{
	// Close and reopen file, clearing it in the process
	passFile.close();
	auto options = ios::out | ios::in | ios::trunc;
	passFile.open(filepath, options);

	// Delete all passwords in memory
	for (int i = 0; i < 20000; i++) {
		if (passwords[i])
			delete passwords[i];
	}
}

string* PasswordAnalyser::GenerateRepetitivePass(int length)
{
	vector<int> password;

	for (int i = 0; i < length; i++) {
		auto it = validChars.begin();
		advance(it, rand() % validChars.size());
		password.emplace_back(*it);
	}

	string* x = new string();
	*x = pe->EncryptPass(password);

	return x;
}

string* PasswordAnalyser::GenerateNonRepetitivePass(int length)
{
	vector<int> password;

	while (password.size() < length) {
		int x = (rand() % 255) + 1;
		if (find(password.begin(), password.end(), x) == password.end()) {
			password.emplace_back(x);
		}
	}

	string* x = new string();
	*x = pe->EncryptPass(password);

	return x;
}


/*
decryptedPasswords = vector of passwords that fit the encrypted password given
decrypted = decrypted password string built up over time
remaining = remaining piece of hashed password
*/
void PasswordAnalyser::DecryptPassword(vector<vector<int>>& decryptedPasswords, vector<int>& decrypted, string remaining, int offset) {
	if (remaining.length() == 0) {
		decryptedPasswords.emplace_back(decrypted);
		//for (auto i : decrypted) {
		//	cout << char(i);
		//}cout << endl;

		//string sentence = "";
		//for (auto x : decrypted) {
		//	sentence += char(x);
		//}
		return;
	}

	for (int i = 1; i < 256; i++) {
		int x = pe->CollatzConjecture(i + offset);
		if (x == stoi(remaining.substr(0, to_string(x).length()))) {
			decrypted.emplace_back(i);
			DecryptPassword(decryptedPasswords, decrypted, remaining.substr(to_string(x).length()), x);
			decrypted.pop_back();
		}
	}
}

void PasswordAnalyser::SmartDecrypt(map<int, set<int>>& possibilities, string password, int offset)
{
	if (password.length() == 0) {
		return;
	}

	// Generate ASCII values with given offset
	set<int> possibleValues;

	for (int i = 1; i < 256; i++) {
		int x = pe->CollatzConjecture(i + offset);
		possibleValues.insert(x);
	}

	// Go through ASCII values and see if they match
	for (int x : possibleValues) {

		string test = to_string(x);

		if (test == password.substr(0, test.length())) {
			set<int> p;
			auto it = possibilities.find(offset);
			if (it != possibilities.end())
				p = it->second;
			p.insert(x);

			possibilities.insert_or_assign(offset, p);
			SmartDecrypt(possibilities, password.substr(test.length()), stoi(password.substr(0, test.length())));
		}
	}
}
void PasswordAnalyser::LetterPlacement(set<vector<int>>& combinations, vector<int>& letterPlacement, map<int, set<int>> possibilities, string password, int maxSize, int previousSize)
{
	for (int i = 1; i <= maxSize; i++) {
		string consider = password.substr(password.length() - i);
		
		for (auto x : possibilities) {
			for (auto y : x.second) {
				if (to_string(y) == consider) {
					string remainingPass = password.substr(0, password.length() - i);

					if (remainingPass.length() == 0) {
						letterPlacement.emplace_back(y);
						vector<int> copy(letterPlacement);
						reverse(copy.begin(), copy.end());
						for (auto x : copy) {
							cout << x << " ";
						} cout << endl;
						letterPlacement.pop_back();
						return;
					}
					//TODO: Trace Table showing erronious results
					/*
					20 9 5 3 9 8 5
					20 95 3 9 8 5 // NOT POSSIBLE
					20 9 5 39 8 5
					20 95 39 8 5
					20 9 5 39 8 5
					20 95 39 8 5
					20 9 5 3 9 8 5
					20 95 3 9 8 5
					20 9 5 39 8 5
					20 95 39 8 5
					20 9 5 39 8 5
					20 95 39 8 5
					20 9 5 3 98 5
					20 95 3 98 5
					20 9 5 3 9 85
					20 95 3 9 85
					20 9 5 39 85
					20 95 39 85
					20 9 5 39 85
					20 95 39 85
					20 9 5 3 9 85
					20 95 3 9 85
					20 9 5 39 85
					20 95 39 85
					20 9 5 39 85
					20 95 39 85
					*/

					if (to_string(x.first).length() <= remainingPass.length()) {
						if (to_string(x.first) == remainingPass.substr(remainingPass.length() - to_string(x.first).length())) {
							letterPlacement.emplace_back(y);
							LetterPlacement(combinations, letterPlacement, possibilities, remainingPass, maxSize);
							letterPlacement.pop_back();
						}
					}
				}
			}
		}
	}
}
//
//void PasswordAnalyser::LetterPlacement(vector<vector<int>>& letters, vector<int>& letterPlacement, map<int, set<int>> possibilities, string password, int offset)
//{
//	if (letterPlacement.size() > password.length()) {
//		cout << "Too Long!!" << endl;
//		return;
//	}
//		
//
//	auto it = possibilities.find(offset);
//	if (it != possibilities.end()) {
//		for (auto x : it->second) {
//			letterPlacement.emplace_back(x);
//			LetterPlacement(letters, letterPlacement, possibilities, password, x);
//			letterPlacement.pop_back();
//		}
//	}
//	else {
//		string test = "";
//
//		for (int x : letterPlacement) {
//			test += to_string(x);
//		}
//
//		if (test == password) {
//			for (int x : letterPlacement) {
//				cout << x << " ";
//			} cout << endl;
//		}
//		
//		return;
//	}
//}
//
//void PasswordAnalyser::Letter_Placement(vector<int>& letterPlacement, map<int, set<int>> possibilities, string password, int key)
//{
//
//
//	for (auto x : possibilities) {
//		for (int y : x.second) {
//
//			//string test = password.substr(password.size() - considerValue.length());
//			if (y == key || (key < 0 && y < 0)) {
//				string considerValue;
//
//				if (key < 0)
//					considerValue = to_string(y * -1);
//				else
//					considerValue = to_string(y);
//
//				if (x.first == 0) {
//					letterPlacement.emplace_back(y);
//					vector<int> copy(letterPlacement);
//					reverse(copy.begin(), copy.end());
//					for (int x : copy) {
//						cout << x << " ";
//					} cout << endl;
//					letterPlacement.pop_back();
//					return;
//				}
//
//				string remaining = password.substr(0, password.size() - considerValue.length());
//				string considerKey = to_string(x.first);
//				string test = remaining.substr(remaining.size() - considerKey.length());
//				if (considerKey == test) {
//					if (key == -1) {
//						letterPlacement.emplace_back(y * -1);
//					}
//					else {
//						letterPlacement.emplace_back(y);
//					}
//					
//					Letter_Placement(letterPlacement, possibilities, remaining, x.first);
//					letterPlacement.pop_back();
//				}
//					
//			}
//		}
//	}
//}
