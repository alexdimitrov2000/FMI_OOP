#include "Cell.h"

const unsigned int MAX_PRODUCTS_IN_CELL = 3;

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

	this->products.clear();
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

bool Cell::isEmpty() const {
	return this->products.size() == 0;
}

void Cell::addProduct(Product* product) {
	this->products.push_back(product);

	this->isCellFull = this->products.size() >= MAX_PRODUCTS_IN_CELL;
}

void Cell::deleteProduct(Product* product) {
	for (vector<Product*>::iterator i = this->products.begin(); i != this->products.end(); i++) {
		if (*i == product) {
			delete product;
			this->products.erase(i);
			break;
		}
	}

	this->isCellFull = this->products.size() >= MAX_PRODUCTS_IN_CELL;
}