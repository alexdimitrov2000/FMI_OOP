#include "Shelf.h"

const unsigned int MAX_CELLS_ON_SHELF = 5;

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

	this->cells.clear();
}

bool Shelf::isFull() const {
	return this->isShelfFull;
}

void Shelf::isFull(bool isFull) {
	this->isShelfFull = isFull;
}

Cell* Shelf::at(size_t index) {
	return this->cells[index];
}

void Shelf::addCell(Cell* cell) {
	this->cells.push_back(cell);

	this->isShelfFull = this->cells.size() >= MAX_CELLS_ON_SHELF;
}