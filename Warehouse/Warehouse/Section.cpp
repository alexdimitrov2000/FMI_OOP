#include "Section.h"

const unsigned int MAX_SHELVES_IN_SECTION = 5;

Section::Section() : shelves(), type(), isSectionFull(false) {}

Section::Section(const SectionType& name) : shelves(), type(name), isSectionFull(false) {}

Section::Section(const Section& other) : shelves(other.shelves), type(other.type), isSectionFull(other.isSectionFull) {}

Section& Section::operator=(const Section& other) {
	if (this != &other) {
		this->shelves = other.shelves;
		this->type = other.type;
		this->isSectionFull = other.isSectionFull;
	}

	return *this;
}

Section::~Section() {
	for (Shelf* shelf : this->shelves) {
		delete shelf;
	}
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

void Section::setType(const SectionType& type) {
	this->type = type;
}

void Section::addShelf(Shelf* shelf) {
	this->shelves.push_back(shelf);

	this->isSectionFull = this->shelves.size() >= MAX_SHELVES_IN_SECTION;
}