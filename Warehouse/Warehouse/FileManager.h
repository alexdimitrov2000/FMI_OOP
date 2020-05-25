#pragma once
#include <string>
#include <vector>
#include "Product.h"
using namespace std;

class FileManager {
private:
	vector<string> lines;
	string filePath;
	bool isOpened;
	vector<Product*> products;

public:
	FileManager();

	bool isFileOpened() const;
	void isFileOpened(bool isOpened);

	void open(const string& filePath);
	void save();
	void saveAs(const string& filePath);
	void close();
	void help();

	vector<string> getFileContent() const;
	void setProducts(const vector<Product*>& products);
};