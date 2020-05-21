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