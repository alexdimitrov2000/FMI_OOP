#pragma once
#include <vector>
#include "Product.h"

const unsigned int MAX_PRODUCTS_IN_CELL = 5;

class Cell {
private:
	vector<Product*> products;
	bool isCellFull;

public:
	Cell();
	Cell(const Cell& other);
	Cell& operator=(const Cell& other);
	~Cell();

	bool isFull() const; // gets the value of this->isCellFull
	void isFull(bool isFull); // sets value of this->isCellFull

	vector<Product*> getProducts() const;

	void addProduct(Product* product);
	//void removeProduct();
};