#include <iostream>
#include <fstream>
#include "FileManager.h"

const string OPEN_SUCCESS = "Successfully opened ";
const string OPEN_FAIL = "Failed to open the file";
const string SAVE_SUCCESS = "Successfully saved ";
const string SAVE_FAIL = "Failed to save the file";
const string CLOSE_SUCCESS = "Successfully closed ";
const string CLOSE_FAIL = "Failed to close the file";
const string HELP_MESSAGE = "The following commands are supported:\n"
							"open <file>	opens <file>\n"
							"close		closes currently opened file\n"
							"save		saves the currently open file\n"
							"saveAs <file>	saves the currently open file in <file>\n"
							"help		prints this information\n"
							"exit		exits the program";

FileManager::FileManager() : lines(), filePath(), isOpened() {}

void FileManager::open(const string& filePath) {
	this->filePath = filePath;

	ifstream input;
	input.open(filePath, ios::in);

	string line;
	if (input.is_open())
	{
		this->isOpened = true;
		while (!input.eof())
		{
			getline(input, line);
			this->lines.push_back(line);
		}

		input.close();
	}
	else {
		ofstream output(filePath, ios::out);
		output.close();
	}

	cout << OPEN_SUCCESS << filePath << endl;
}

void FileManager::save() {
	this->saveAs(this->filePath);
}

void FileManager::saveAs(const string& filePath) {
	ofstream output;

	output.open(filePath, ios::out);

	if (output.is_open())
	{
		int linesCnt = this->lines.size();
		for (size_t i = 0; i < linesCnt; i++)
		{
			output << this->lines[i];

			if (i + 1 != linesCnt)
			{
				output << '\n';
			}
		}

		output.close();

		cout << SAVE_SUCCESS << filePath << endl;
	}
	else {
		cout << SAVE_FAIL << endl;
	}
}

void FileManager::close() {
	this->isOpened = false;
	this->lines.clear();
	cout << CLOSE_SUCCESS << this->filePath << endl;
}

void FileManager::help() {
	cout << HELP_MESSAGE << endl;
}

vector<string> FileManager::getFileContent() const {
	return this->lines;
}