#pragma once
#include <string>
#include <vector>
using namespace std;

class FileManager {
private:
	vector<string> lines;
	string filePath;
	bool isOpened;

public:
	FileManager();

	void open(const string& filePath);
	void save();
	void saveAs(const string& filePath);
	void close();
	void help();

	vector<string> getFileContent() const;
};