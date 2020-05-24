#pragma once
#include "Cell.h"

class Shelf {
private:
	vector<Cell*> cells;
	bool isShelfFull;

public:
	Shelf();
	Shelf(const Shelf& other);
	Shelf& operator=(const Shelf& other);
	~Shelf();

	bool isFull() const; // getter for this->isShelfFull
	void isFull(bool isFull); // setter for this->isShelfFull

	vector<Cell*> getCells() const;
	Cell* at(size_t index);
	void addCell(Cell* cell);
};