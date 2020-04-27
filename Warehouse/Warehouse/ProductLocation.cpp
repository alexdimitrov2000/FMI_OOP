#include "ProductLocation.h"

ProductLocation::ProductLocation() {
	this->section = 0;
	this->shelf = 0;
	this->number = 0;
}

ProductLocation::ProductLocation(unsigned int section, unsigned int shelf, unsigned int number) {
	this->section = section;
	this->shelf = shelf;
	this->number = number;
}

ProductLocation::ProductLocation(const ProductLocation& other) {
	this->section = other.section;
	this->shelf = other.shelf;
	this->number = other.number;
}

ProductLocation& ProductLocation::operator=(const ProductLocation& other) {
	if (this != &other) {
		this->section = other.section;
		this->shelf = other.shelf;
		this->number = other.number;
	}

	return *this;
}

unsigned int ProductLocation::getSection() const {
	return this->section;
}

unsigned int ProductLocation::getShelf() const {
	return this->shelf;
}

unsigned int ProductLocation::getNumber() const {
	return this->number;
}

void ProductLocation::setSection(const unsigned int section) {
	this->section = section;
}

void ProductLocation::setShelf(const unsigned int shelf) {
	this->shelf = shelf;
}

void ProductLocation::setNumber(const unsigned int number) {
	this->number = number;
}