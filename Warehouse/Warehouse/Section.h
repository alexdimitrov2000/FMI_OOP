#pragma once
#include "Shelf.h"

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
	Shelf* at(size_t index);

	void setName(const string& name);
	void addShelf(Shelf* shelf);
};