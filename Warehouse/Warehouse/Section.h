#pragma once
#include "Shelf.h"
#include "SectionType.h"

class Section {
private:
	vector<Shelf*> shelves;
	SectionType type;
	bool isSectionFull;

public:
	Section();
	Section(const SectionType& type);
	Section(const Section& other);
	Section& operator=(const Section& other);
	~Section();

	bool isFull() const; // getter for this->isSectionFull
	void isFull(bool isFull); // setter for this->isSectionFull

	SectionType getType() const;
	Shelf* at(size_t index);

	void setType(const SectionType& type);
	void addShelf(Shelf* shelf);
};