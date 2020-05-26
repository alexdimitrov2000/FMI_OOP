#pragma once
#include "Shelf.h"
#include "SectionType.h"

class Section {
private:
	vector<Shelf*> shelves;
	SectionType type;
	bool isSectionFull;
	vector<Product*> products;

	int getNumberOfProductsWithName(const string& name);
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
	vector<Product*> getProducts() const;
	vector<Shelf*> getShelves() const;
	bool containsProductWithName(const string& name);
	Product* getProductByName(const string& name);
	vector<Product*> getAllWithName(const string& name);

	void setType(const SectionType& type);
	void addShelf(Shelf* shelf);
	void addToSectionProducts(Product* product);
	void deleteFromSectionProducts(Product* product);
};