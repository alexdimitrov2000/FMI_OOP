#pragma once

class ProductLocation {
private:
	unsigned int section;
	unsigned int shelf;
	unsigned int cell;

public:
	ProductLocation();
	ProductLocation(unsigned int section, unsigned int shelf, unsigned int cell);
	ProductLocation(const ProductLocation& other);
	ProductLocation& operator=(const ProductLocation& other);
	
	unsigned int getSection() const;
	unsigned int getShelf() const;
	unsigned int getCell() const;

	void setSection(const unsigned int section);
	void setShelf(const unsigned int shelf);
	void setCell(const unsigned int cell);
};