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

Shelf::Shelf() : cells(), isShelfFull(false) {}

Shelf::Shelf(const Shelf& other) : cells(other.cells), isShelfFull(other.isShelfFull) {}

Shelf& Shelf::operator=(const Shelf& other) {
	if (this != &other) {
		this->cells = other.cells;
		this->isShelfFull = other.isShelfFull;
	}

	return *this;
}

Shelf::~Shelf() {
	for (Cell* cell : this->cells) {
		delete cell;
	}
}

bool Shelf::isFull() const {
	return this->isShelfFull;
}

void Shelf::isFull(bool isFull) {
	this->isShelfFull = isFull;
}

Cell* Shelf::operator[](size_t index) {
	return this->cells[index];
}

void Shelf::addCell(Cell* cell) {
	this->cells.push_back(cell);

	this->isShelfFull = this->cells.size() >= MAX_CELLS_ON_SHELF;
}