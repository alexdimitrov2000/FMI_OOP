#include <iostream>
#include <sstream>
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
							"saveas <file>	saves the currently open file in <file>\n"
							"help		prints this information\n"
							"operations	prints supported operations\n"
							"exit		exits the program";
const string LOGS = "logs-";
const string SPACE_DELIMITER = " ";
const string ADDED = "Added ";

FileManager::FileManager() : lines(), logsData(), filePath(), isOpened(), products() {}

bool FileManager::isFileOpened() const {
	return this->isOpened;
}

void FileManager::isFileOpened(bool isOpened) {
	this->isOpened = isOpened;
}

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
		int productsCnt = this->products.size();
		for (size_t i = 0; i < productsCnt; i++)
		{
			output << (*this->products[i]);

			if (i + 1 != productsCnt)
			{
				output << '\n';
			}
		}

		output.close();

		this->saveLogsFile(filePath);

		cout << SAVE_SUCCESS << filePath << endl;
	}
	else {
		cout << SAVE_FAIL << endl;
	}
}

void FileManager::saveLogsFile(const string& filePath) {
	ofstream output;
	string logsFilePath = (LOGS + filePath);

	output.open(logsFilePath, ios::out | ios::app);


	if (output.is_open())
	{
		for (string& line : this->logsData) {
			output << line << endl;
		}

		output.close();
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

void FileManager::logsAddProduct(const Product* product) {
	ostringstream buffer;
	buffer << product->getEntryDate() << SPACE_DELIMITER << ADDED << product->getAvailableQuantity()
		<< SPACE_DELIMITER << product->getName() << SPACE_DELIMITER << product->getManufacturerName();
	
	this->logsData.push_back(buffer.str());
}

vector<string> FileManager::getFileContent() const {
	return this->lines;
}

void FileManager::setProducts(const vector<Product*>& products) {
	this->products = products;
}