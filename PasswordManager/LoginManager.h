#pragma once
#include "FileHandler.h"

using namespace std;

struct login {
	string username;
	string passHash;
};

class LoginManager : public FileHandler {
public:
	LoginManager(string filepath);
	~LoginManager();

	bool CheckFile(login l);
	string AddLogin(login l);

private:
	map<string, string> logins;
};