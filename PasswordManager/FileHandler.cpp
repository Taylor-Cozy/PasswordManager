#include "FileHandler.h"
#include <iostream>

FileHandler::FileHandler(string filepath) throw (invalid_argument)
{
	auto options = ios::out | ios::in | ios::app;
	passFile.open(filepath, options);
	if (passFile.fail())
		throw invalid_argument("Unable to open or create file: " + filepath);

}

FileHandler::~FileHandler()
{
	passFile.close();
}

void FileHandler::WriteFile(string record)
{
	passFile.clear();
	passFile.seekg(ios::end);
	passFile << record << "\n";
}


