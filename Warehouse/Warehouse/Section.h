#pragma once
#include "Shelf.h"

const unsigned int MAX_SHELVES_IN_SECTION = 5;

class Section {
private:
	vector<Shelf*> shelves;
	string name;
	bool isSectionFull;

public:
	Section();
	Section(const string& name);
	Section(const Section& other);
	Section& operator=(const Section& other);
	~Section();

	bool isFull() const; // getter for this->isSectionFull
	void isFull(bool isFull); // setter for this->isSectionFull

	string getName() const;
	Shelf* operator[](size_t index);

	void setName(const string& name);
	void addShelf(Shelf* shelf);
};

Section::Section() : shelves(), name(), isSectionFull(false) {}

Section::Section(const string& name) : shelves(), name(name), isSectionFull(false) {}

Section::Section(const Section& other) : shelves(other.shelves), name(other.name), isSectionFull(other.isSectionFull) {}

Section& Section::operator=(const Section& other) {
	if (this != &other) {
		this->shelves = other.shelves;
		this->name = other.name;
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

string Section::getName() const {
	return this->name;
}

Shelf* Section::operator[](size_t index) {
	return this->shelves[index];
}

void Section::setName(const string& name) {
	this->name = name;
}

void Section::addShelf(Shelf* shelf) {
	this->shelves.push_back(shelf);

	this->isSectionFull = this->shelves.size() >= MAX_SHELVES_IN_SECTION;
}