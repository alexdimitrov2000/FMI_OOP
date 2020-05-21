#pragma once
#include "Cell.h"

const unsigned int MAX_CELLS_ON_SHELF = 10;

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

	Cell* operator[](size_t index);
	void addCell(Cell* cell);
};