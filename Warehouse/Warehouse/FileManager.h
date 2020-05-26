#pragma once
#include <string>
#include <vector>
#include "Product.h"
using namespace std;

class FileManager {
private:
	vector<string> lines;
	vector<string> logsData;
	string filePath;
	string logsFilePath;
	bool isOpened;
	vector<Product*> products;

	void openLogsFile();
	void saveLogsFile(const string& path);
public:
	FileManager();

	bool isFileOpened() const;
	void isFileOpened(bool isOpened);

	void open(const string& filePath);
	void save();
	void saveAs(const string& filePath);
	void close();
	void help();

	void logsAddProduct(const Product* product);
	void logsRemoveProduct(const Product* product, const string& removedQuantity);
	void showLogInInterval(const string& from, const string& to);
	void logsCleanWarehouse();

	vector<string> getFileContent() const;
	void setProducts(const vector<Product*>& products);
};