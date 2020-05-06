#include "Product.h"
#include <cstring>

Product::Product() : name(""), manufacturerName(""), unit(""), expiryDate(), entryDate(), availableQuantity(0), location(), comment("") {}

Product::Product(const string& name, const string& manufacturerName, const string& unit, const Date& expiryDate, const Date& entryDate, 
				unsigned int availableQuantity, const ProductLocation& location, const string& comment) 
				: name(name), manufacturerName(manufacturerName), unit(unit), expiryDate(expiryDate), entryDate(entryDate), availableQuantity(availableQuantity), location(location), comment(comment) {}

Product::Product(const Product& other) 
				: name(other.name), manufacturerName(other.manufacturerName), unit(other.unit), expiryDate(other.expiryDate), entryDate(other.entryDate), 
				  availableQuantity(other.availableQuantity), location(other.location), comment(other.comment) {}

Product& Product::operator=(const Product& other) {
	if (this != &other)
	{
		this->name = other.name;
		this->manufacturerName = other.manufacturerName;
		this->unit = other.unit;
		this->expiryDate = other.expiryDate;
		this->entryDate = other.entryDate;
		this->availableQuantity = other.availableQuantity;
		this->location = other.location;
		this->comment = other.comment;
	}

	return *this;
}

Product::~Product() {}

string Product::getName() const {
	return this->name;
}

string Product::getManufacturerName() const {
	return this->manufacturerName;
}

string Product::getUnit() const {
	return this->unit;
}

Date Product::getExpiryDate() const {
	return this->expiryDate;
}

Date Product::getEntryDate() const {
	return this->entryDate;
}

unsigned int Product::getAvailableQuantity() const {
	return this->availableQuantity;
}

ProductLocation Product::getLocation() const {
	return this->location;
}

string Product::getComment() const {
	return this->comment;
}

void Product::setName(const string& name) {
	this->name = name;
}

void Product::setManufacturerName(const string& manufacturerName) {
	this->manufacturerName = manufacturerName;
}

void Product::setUnit(const string& unit) {
	this->unit = unit;
}

void Product::setExpiryDate(const Date& expiryDate) {
	this->expiryDate = expiryDate;
}

void Product::setEntryDate(const Date& entryDate) {
	this->entryDate = entryDate;
}

void Product::setAvailableQuantity(const unsigned int quantity) {
	this->availableQuantity = quantity;
}

void Product::setLocation(const ProductLocation& location) {
	this->location = location;
}

void Product::setComment(const string& comment) {
	this->comment = comment;
}