#include <iostream>
#include <sstream>
#include <fstream>
#include "FileManager.h"
#include "DateHelper.h"
#include "StringHelper.h"

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
const string REMOVED = "Removed ";
const string CLEANED_WAREHOUSE = "Cleaned warehouse";

FileManager::FileManager() : lines(), logsData(), filePath(), isOpened(), products() {}

bool FileManager::isFileOpened() const {
	return this->isOpened;
}

void FileManager::isFileOpened(bool isOpened) {
	this->isOpened = isOpened;
}

void FileManager::openLogsFile() {
	ifstream input;
	input.open(this->logsFilePath, ios::in);

	string line;
	if (input.is_open())
	{
		while (!input.eof())
		{
			getline(input, line);
			this->logsData.push_back(line);
		}

		input.close();
	}
	else {
		ofstream output(this->logsFilePath, ios::out);
		output.close();
	}
}

void FileManager::open(const string& filePath) {
	this->filePath = filePath;
	this->logsFilePath = (LOGS + filePath);

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

		this->openLogsFile();
	}
	else {
		ofstream output(filePath, ios::out);
		this->openLogsFile();
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
		for (int i = 0; i < productsCnt; i++)
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

void FileManager::saveLogsFile(const string& path) {
	ofstream output;
	string logsPath = this->logsFilePath;
	if (path != this->filePath)
		logsPath = (LOGS + path);

	output.open(logsPath, ios::out);

	if (output.is_open())
	{
		int linesCnt = this->logsData.size();
		for (int i = 0; i < linesCnt; i++)
		{
			output << this->logsData[i];

			if (i + 1 != linesCnt)
			{
				output << '\n';
			}
		}

		output.close();
	}
	else {
		cout << SAVE_FAIL << endl;
	}
}

void FileManager::showLogInInterval(const string& from, const string& to) {
	Date fromDate(from);
	Date toDate(to);

	for (string& line : this->logsData) {
		Date logDate(StringHelper::split(line)[0]);

		if (fromDate <= logDate && logDate <= toDate) {
			cout << line << endl;
		}
	}
}

void FileManager::close() {
	this->isOpened = false;
	this->lines.clear();
	this->logsData.clear();
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

void FileManager::logsRemoveProduct(const string& productName, const string& removedQuantity) {
	ostringstream buffer;
	buffer << DateHelper::getTodaysDate() << SPACE_DELIMITER << REMOVED << removedQuantity << SPACE_DELIMITER << productName;

	this->logsData.push_back(buffer.str());
}

void FileManager::logsCleanWarehouse() {
	Date today = DateHelper::getTodaysDate();

	ostringstream buffer;
	buffer << today << SPACE_DELIMITER << CLEANED_WAREHOUSE;

	this->logsData.push_back(buffer.str());
}

vector<string> FileManager::getFileContent() const {
	return this->lines;
}

void FileManager::setProducts(const vector<Product*>& products) {
	this->products = products;
}