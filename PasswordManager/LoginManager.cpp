#include "LoginManager.h"

LoginManager::LoginManager(string filepath) : FileHandler(filepath) {
	passFile.clear();
	passFile.seekg(ios::beg);

	string text;
	int split;

	while (getline(passFile, text)) {
		split = text.find(' ');
		logins.insert(pair<string, string>(text.substr(0, split), text.substr(split + 1)));
	}
}

LoginManager::~LoginManager()
{
}

bool LoginManager::CheckFile(login l)
{
	auto index = logins.find(l.username);
	if (index->second == l.passHash)
		return true;

	return false;
}

string LoginManager::AddLogin(login l)
{
	if (logins.find(l.username) != logins.end())
		return "User already exists.";

	WriteFile(l.username + " " + l.passHash);
	logins.insert(pair<string, string>(l.username, l.passHash));
	return "User created.";
}
