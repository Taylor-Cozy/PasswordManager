#include "FileHandler.h"
#include <iostream>

FileHandler::FileHandler(string filepath)
{
	//file = new fstream(filePath);
	//file->open(filePath);

	//TODO: Handle multiple file openings, throw exceptions
	passFile.open(filepath, ios::out | ios::in | ios::app);
}

FileHandler::~FileHandler()
{
	passFile.close();
}

void FileHandler::checkFile()
{
	string text;
	passFile.seekg(ios::beg);
	while (getline(passFile, text))
		cout << text;
}

void FileHandler::writeFile(login l)
{
	passFile.seekg(ios::end);
	passFile << l.username << " " << l.passHash << "\n";
}
