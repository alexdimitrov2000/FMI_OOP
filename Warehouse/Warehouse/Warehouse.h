#pragma once
#include "Section.h"

class Warehouse {
private:
	vector<Section*> sections;
	bool isWarehouseFull;

	unsigned int removeProduct(Product* product, unsigned int quantityToRemove);
public:
	Warehouse();
	Warehouse(const Warehouse& other);
	Warehouse& operator=(const Warehouse& other);
	~Warehouse();

	bool isFull() const; // getter for this->isWarehouseFull
	void isFull(bool isFull); // setter for this->isWarehouseFull

	void addSection(Section* section);
	int getSectionIndexByType(const string& type);
	ProductLocation findLocationForProduct(int sectionIndex, const string& name, Date expiration);

	Section* at(size_t index);
	void build();
	void destroy();
	void addFileProducts(vector<string> fileLines);
	void printProducts();
	vector<Product*> getProducts();
	Product* addProduct(vector<string> tokens);
	unsigned int remove(string name, string quantityStr);
	void clean();
};