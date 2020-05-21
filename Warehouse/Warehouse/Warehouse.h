#pragma once
#include "Section.h"

class Warehouse {
private:
	vector<Section*> sections;
	vector<Product*> allProducts;
	bool isWarehouseFull;

public:
	Warehouse();
	Warehouse(const Warehouse& other);
	Warehouse& operator=(const Warehouse& other);
	~Warehouse();

	bool isFull() const; // getter for this->isWarehouseFull
	void isFull(bool isFull); // setter for this->isWarehouseFull

	void addSection(Section* section);

	Section* at(size_t index);
	void build();
};