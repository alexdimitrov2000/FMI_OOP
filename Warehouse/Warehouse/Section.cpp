#include <algorithm>
#include "Section.h"

const unsigned int MAX_SHELVES_IN_SECTION = 5;

Section::Section() : shelves(), type(), isSectionFull(false), products() {}

Section::Section(const SectionType& name) : shelves(), type(name), isSectionFull(false), products() {}

Section::Section(const Section& other) : shelves(other.shelves), type(other.type), isSectionFull(other.isSectionFull), products(other.products) {}

Section& Section::operator=(const Section& other) {
	if (this != &other) {
		this->shelves = other.shelves;
		this->type = other.type;
		this->isSectionFull = other.isSectionFull;
		this->products = other.products;
	}

	return *this;
}

Section::~Section() {
	for (Shelf* shelf : this->shelves) {
		delete shelf;
	}

	this->shelves.clear();
}

bool Section::isFull() const {
	return this->isSectionFull;
}

void Section::isFull(bool isFull) {
	this->isSectionFull = isFull;
}

SectionType Section::getType() const {
	return this->type;
}

Shelf* Section::at(size_t index) {
	return this->shelves[index];
}

vector<Product*> Section::getProducts() const {
	return this->products;
}

vector<Shelf*> Section::getShelves() const {
	return this->shelves;
}

bool Section::containsProductWithName(const string& name) {
	return count_if(this->products.begin(), this->products.end(), [name](Product* prod) { return prod->getName() == name; }) != 0;
}

Product* Section::getProductByName(const string& name) {
	if (!this->containsProductWithName(name)) {
		return nullptr;
	}

	vector<Product*>::iterator product = find_if(this->products.begin(), this->products.end(), [name](Product* prod) { return prod->getName() == name; });

	return *product;
}

void Section::setType(const SectionType& type) {
	this->type = type;
}

void Section::addShelf(Shelf* shelf) {
	this->shelves.push_back(shelf);

	this->isSectionFull = this->shelves.size() >= MAX_SHELVES_IN_SECTION;
}

void Section::addToSectionProducts(Product* product) {
	this->products.push_back(product);
}