#include "ProductLocation.h"
#include "StringHelper.h"

const char LOCATION_DELIMITER = '-';

ProductLocation::ProductLocation() : section(0), shelf(0), cell(0) {}

ProductLocation::ProductLocation(const string& location) {
	vector<string> tokens = StringHelper::split(location, LOCATION_DELIMITER);

	this->section = StringHelper::convertToInt(tokens[0]);
	this->shelf = StringHelper::convertToInt(tokens[1]);
	this->cell = StringHelper::convertToInt(tokens[2]);
}

ProductLocation::ProductLocation(unsigned int section, unsigned int shelf, unsigned int cell) : section(section), shelf(shelf), cell(cell) {}

ProductLocation::ProductLocation(const ProductLocation& other) : section(other.section), shelf(other.shelf), cell(other.cell) {}

ProductLocation& ProductLocation::operator=(const ProductLocation& other) {
	if (this != &other) {
		this->section = other.section;
		this->shelf = other.shelf;
		this->cell = other.cell;
	}

	return *this;
}

unsigned int ProductLocation::getSection() const {
	return this->section;
}

unsigned int ProductLocation::getShelf() const {
	return this->shelf;
}

unsigned int ProductLocation::getCell() const {
	return this->cell;
}

void ProductLocation::setSection(const unsigned int section) {
	this->section = section;
}

void ProductLocation::setShelf(const unsigned int shelf) {
	this->shelf = shelf;
}

void ProductLocation::setCell(const unsigned int cell) {
	this->cell = cell;
}

ostream& operator<<(ostream& output, const ProductLocation& location) {
	output << location.section << LOCATION_DELIMITER << location.shelf << LOCATION_DELIMITER << location.cell;
	return output;
}