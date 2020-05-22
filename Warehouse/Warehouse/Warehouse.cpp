#include "Warehouse.h"

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
}