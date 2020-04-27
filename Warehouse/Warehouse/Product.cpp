#include "Product.h"
#include <cstring>

Product::Product() : location() {
	this->name = nullptr;
	this->manufacturerName = nullptr;
	this->unit = nullptr;
	this->availableQuantity = 0;
	this->comment = nullptr;
}

Product::Product(const char* name, const char* manufacturerName, const char* unit, unsigned int availableQuantity, const ProductLocation& location, const char* comment) {
	this->setName(name);
	this->setManufacturerName(manufacturerName);
	this->setUnit(unit);
	this->availableQuantity = availableQuantity;
	this->location = location;
	this->setComment(comment);
}

void Product::setName(const char* name) {
	delete[] this->name;

	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
}

void Product::setManufacturerName(const char* manufacturerName) {
	delete[] this->manufacturerName;

	this->manufacturerName = new char[strlen(manufacturerName) + 1];
	strcpy_s(this->manufacturerName, strlen(manufacturerName) + 1, manufacturerName);
}

void Product::setUnit(const char* unit) {
	delete[] this->unit;

	this->unit = new char[strlen(unit) + 1];
	strcpy_s(this->unit, strlen(unit) + 1, unit);
}

void Product::setAvailableQuantity(const unsigned int quantity) {
	this->availableQuantity = quantity;
}

void Product::setLocation(const ProductLocation& location) {
	this->location = location;
}

void Product::setComment(const char* comment) {
	delete[] this->comment;

	this->comment = new char[strlen(comment) + 1];
	strcpy_s(this->comment, strlen(comment) + 1, comment);
}