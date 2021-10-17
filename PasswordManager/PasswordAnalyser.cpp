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

void PasswordAnalyser::SmartDecrypt(map<int, vector<int>>& possibilities, string password, int offset)
{
	if (password.substr(0, 1) == "0")
		return;

	vector<int> possibleValues;

	for (int i = 1; i < 256; i++) {
		int x = pe->CollatzConjecture(i + offset);
		if (to_string(x) == password) {
			vector<int> finished;
			auto it = possibilities.find(offset);
			if (it != possibilities.end())
				finished = it->second;
			finished.emplace_back(stoi(password));
			possibilities.insert(pair<int, vector<int>>(offset, finished));
			return;
		}
		possibleValues.emplace_back(x);
	}

	int limit = to_string(*max_element(begin(possibleValues), end(possibleValues))).length();

	vector<int> solved;

	for (int i = 1; i < password.length(); i++) {

		if (i > limit)
			break;

		int number = stoi(password.substr(0, i));
		
		for (auto x : possibleValues) {
			if (number == x) {
				solved.emplace_back(number);
				break;
			}
		}
	}

	if(solved.size() > 0)
		possibilities.insert(pair<int, vector<int>>(offset, solved));

	for (auto x : solved) {
		string remaining = password.substr(to_string(x).length());
		SmartDecrypt(possibilities, remaining, x);
	}
}
