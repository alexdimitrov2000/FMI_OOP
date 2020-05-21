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

Cell::Cell() : products(), isCellFull(false) {}

Cell::Cell(const Cell& other) : products(other.products), isCellFull(other.isCellFull) {}

Cell& Cell::operator=(const Cell& other) {
	if (this != &other) {
		this->products = other.products;
		this->isCellFull = other.isCellFull;
	}

	return *this;
}

Cell::~Cell() {
	for (Product* product : this->products) {
		delete product;
	}
}

vector<Product*> Cell::getProducts() const {
	return this->products;
}

bool Cell::isFull() const {
	return this->isCellFull;
}

void Cell::isFull(bool isFull) {
	this->isCellFull = isFull;
}

void Cell::addProduct(Product* product) {
	this->products.push_back(product);

	this->isCellFull = this->products.size() >= MAX_PRODUCTS_IN_CELL;
}