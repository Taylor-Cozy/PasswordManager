#include "FileHandler.h"

FileHandler::FileHandler(string filepath, bool overwrite) throw (invalid_argument) : filepath(filepath)
{
	auto options = ios::out | ios::in;

	if (overwrite)
		options |= ios::trunc;
	else
		options |= ios::app;

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

void FileHandler::CloseFile()
{
	passFile.close();
}


