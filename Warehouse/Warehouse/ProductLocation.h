#pragma once

class ProductLocation {
private:
	unsigned int section;
	unsigned int shelf;
	unsigned int number;

public:
	ProductLocation();
	ProductLocation(unsigned int section, unsigned int shelf, unsigned int number);
	ProductLocation(const ProductLocation& other);
	ProductLocation& operator=(const ProductLocation& other);
	
	unsigned int getSection() const;
	unsigned int getShelf() const;
	unsigned int getNumber() const;

	void setSection(const unsigned int section);
	void setShelf(const unsigned int shelf);
	void setNumber(const unsigned int number);
};