#include <iostream>
#include "Warehouse.h"
#include "StringHelper.h"

const unsigned int MAX_SECTIONS = 3;
const SectionType SECTION_TYPES[] = { SectionType::Foods, SectionType::Drinks, SectionType::Others };

Warehouse::Warehouse() : sections(), allProducts(), isWarehouseFull(false) {}

Warehouse::Warehouse(const Warehouse& other) : sections(other.sections), allProducts(other.allProducts), isWarehouseFull(other.isWarehouseFull) {}

Warehouse& Warehouse::operator=(const Warehouse& other) {
	if (this != &other) {
		this->sections = other.sections;
		this->allProducts = other.allProducts;
		this->isWarehouseFull = other.isWarehouseFull;
	}

	return *this;
}

Warehouse::~Warehouse() {
	this->destroy();
}

bool Warehouse::isFull() const {
	return this->isWarehouseFull;
}

void Warehouse::isFull(bool isFull) {
	this->isWarehouseFull = isFull;
}

void Warehouse::addSection(Section* section) {
	this->sections.push_back(section);

	this->isWarehouseFull = this->sections.size() >= MAX_SECTIONS;
}

Section* Warehouse::at(size_t index) {
	return this->sections[index];
}

void Warehouse::build() {
	int sectionIndex = 0;

	while (!this->isWarehouseFull) {
		Section* section = new Section(SECTION_TYPES[sectionIndex]);

		while (!section->isFull()) {
			Shelf* shelf = new Shelf();

			while (!shelf->isFull())
			{
				shelf->addCell(new Cell());
			}

			section->addShelf(shelf);
		}

		this->addSection(section);
		sectionIndex++;
	}
}

void Warehouse::destroy() {
	for (Section* section : this->sections) {
		delete section;
	}

	this->sections.clear();
}

void Warehouse::addFileProducts(vector<string> fileLines) {
	vector<string> tokens;
	string name, manufacturer, unit, comment;
	unsigned int quantity;
	Product* product = nullptr;

	for (size_t i = 0; i < fileLines.size(); i++)
	{
		tokens = StringHelper::split(fileLines[i]);

		name = tokens[0];
		manufacturer = tokens[1];
		unit = tokens[2];
		Date expiryDate(tokens[3]);
		Date entryDate(tokens[4]);
		quantity = StringHelper::convertToInt(tokens[5]);
		ProductLocation location(tokens[6]);
		comment = StringHelper::concatenate(tokens, tokens.begin() + 7, tokens.end());

		product = new Product(name, manufacturer, unit, expiryDate, entryDate, quantity, location, comment);

		this->sections.at(location.getSection())->at(location.getShelf())->at(location.getCell())->addProduct(product);
		this->allProducts.push_back(product);
	}
}