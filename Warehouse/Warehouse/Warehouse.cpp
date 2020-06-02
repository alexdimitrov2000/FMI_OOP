#include <iostream>
#include "Warehouse.h"
#include "StringHelper.h"
#include "DateHelper.h"

const unsigned int MAX_SECTIONS = 3;
const SectionType SECTION_TYPES[] = { SectionType::Foods, SectionType::Drinks, SectionType::Others };

// Messages
const string NO_PRODUCTS_IN_SECTION_MESSAGE = "No products in section.";
const string ADDED_PRODUCT_SUCCESS_MESSAGE = "The product was successfully added to the warehouse.";
const string CLEANED = "Cleaned ";
const string SPACE_DELIMITER = " ";
const string INEXISTENT_WAREHOUSE_PRODUCT_MESSAGE = "The warehouse does not contain a product with that name.";
const string NO_REMOVED_PRODUCTS_MESSAGE = "No products were removed from ";

const string REMOVE_ALL_QUESTION = "You are trying to remove more products than exist. Do you want to remove all ";
const string NO_ANSWER = "no";
const string REMOVED = "Removed ";
const string FROM = " from ";
const string EXPIRING_ON = " expiring on ";
const string YES_NO = " (yes/no): ";

Warehouse::Warehouse() : sections(), isWarehouseFull(false) {}

Warehouse::Warehouse(const Warehouse& other) : sections(other.sections), isWarehouseFull(other.isWarehouseFull) {}

Warehouse& Warehouse::operator=(const Warehouse& other) {
	if (this != &other) {
		this->sections = other.sections;
		this->isWarehouseFull = other.isWarehouseFull;
	}

	return *this;
}

Warehouse::~Warehouse() {
	this->destroy();
}

bool Warehouse::isFull() const {
	return this->isWarehouseFull;
}

void Warehouse::isFull(bool isFull) {
	this->isWarehouseFull = isFull;
}

void Warehouse::addSection(Section* section) {
	this->sections.push_back(section);

	this->isWarehouseFull = this->sections.size() >= MAX_SECTIONS;
}

int Warehouse::getSectionIndexByType(const string& type) {
	if (type == StringHelper::sectionTypeToString(SECTION_TYPES[0])) return 0;
	if (type == StringHelper::sectionTypeToString(SECTION_TYPES[1])) return 1;
	if (type == StringHelper::sectionTypeToString(SECTION_TYPES[2])) return 2;

	return -1;
}

Section* Warehouse::at(size_t index) {
	return this->sections[index];
}

void Warehouse::build() {
	int sectionIndex = 0;

	while (!this->isWarehouseFull) {
		Section* section = new Section(SECTION_TYPES[sectionIndex]);

		while (!section->isFull()) {
			Shelf* shelf = new Shelf();

			while (!shelf->isFull())
			{
				shelf->addCell(new Cell());
			}

			section->addShelf(shelf);
		}

		this->addSection(section);
		sectionIndex++;
	}
}

void Warehouse::destroy() {
	for (Section* section : this->sections) {
		delete section;
	}

	this->sections.clear();
	this->isWarehouseFull = false;
}

void Warehouse::addFileProducts(vector<string> fileLines) {
	vector<string> tokens;
	string name, manufacturer, unit, comment;
	unsigned int quantity;
	Product* product = nullptr;
	Section* section;

	for (size_t i = 0; i < fileLines.size(); i++)
	{
		if (fileLines[i] == "") {
			continue;
		}

		tokens = StringHelper::split(fileLines[i]);

		name = tokens[0];
		manufacturer = tokens[1];
		unit = tokens[2];
		Date expiryDate(tokens[3]);
		Date entryDate(tokens[4]);
		quantity = StringHelper::convertToInt(tokens[5]);
		ProductLocation location(tokens[6]);
		comment = StringHelper::concatenate(tokens, tokens.begin() + 7, tokens.end());

		product = new Product(name, manufacturer, unit, expiryDate, entryDate, quantity, location, comment);

		section = this->sections.at(location.getSection());
		section->addToSectionProducts(product);
	}
}

void Warehouse::printProducts() {
	for (Section*& section : this->sections) {
		cout << StringHelper::sectionTypeToString(section->getType()) << endl;

		if (section->getProducts().size() == 0) {
			cout << NO_PRODUCTS_IN_SECTION_MESSAGE << endl;
			continue;
		}

		for (Product*& product : section->getProducts()) {
			cout << (*product) << endl;
		}
		cout << endl;
	}
}

vector<Product*> Warehouse::getProducts() {
	vector<Product*> products;

	for (Section*& section : this->sections) {

		if (section->getProducts().size() == 0) {
			continue;
		}

		for (Product*& product : section->getProducts()) {
			products.push_back(product);
		}
	}

	return products;
}

ProductLocation Warehouse::findLocationForProduct(int sectionIndex, const string& name, Date expiration) {
	ProductLocation location(sectionIndex, 0, 0);
	Section* section = this->sections[sectionIndex];
	int shelvesCnt = section->getShelves().size();
	int cellsCnt = section->getShelves()[0]->getCells().size();
	string cellProductsName;
	Shelf* shelf;
	Cell* cell;

	if (!section->containsProductWithName(name)) {
		// logic for getting location when the product name is unique in the warehouse
		for (int i = 0; i < shelvesCnt; i++)
		{
			shelf = section->at(i);

			for (int g = 0; g < cellsCnt; g++)
			{
				cell = shelf->at(g);

				if (cell->isEmpty()) {
					location.setShelf(i);
					location.setCell(g);

					return location;
				}
			}
		}
	}

	Product* existent = section->getProductByName(name);
	int shelfNum = existent->getLocation().getShelf();
	int cellNum = existent->getLocation().getCell();
	cell = section->at(shelfNum)->at(cellNum);

	if (existent->getExpiryDate() == expiration && !cell->isFull()) {
		// logic for getting location when a product with that name is already existent, their expiration dates are equal and the cell has place for the new product
		location.setShelf(shelfNum);
		location.setCell(cellNum);
		return location;
	}

	cellNum++; // no need to check the same cell on the first iretarion
	// logic for getting location when a product with that name is already existent, but either their expiration dates are different or the cell of the existent one is full
	for (int i = shelfNum; i < shelvesCnt; i++)
	{
		shelf = section->at(i);

		for (int g = cellNum; g < cellsCnt; g++)
		{
			cell = shelf->at(g);
			if (cell->isEmpty() || (cell->getProducts()[0]->getName() == name && cell->getProducts()[0]->getExpiryDate() == expiration && !cell->isFull())) {
				location.setShelf(i);
				location.setCell(g);
				return location;
			}
		}
		cellNum = 0;
	}

	return location;
}

Product* Warehouse::addProduct(vector<string> tokens)
{
	int sectionIndex = this->getSectionIndexByType(tokens[0]);
	Section* section = this->sections[sectionIndex];

	string name = tokens[1];
	string manufacturer = tokens[2];
	string unit = tokens[3];
	Date expiryDate(tokens[4]);
	Date entryDate = DateHelper::getTodaysDate();
	unsigned int quantity = StringHelper::convertToInt(tokens[5]);
	ProductLocation location = this->findLocationForProduct(sectionIndex, name, expiryDate);
	string comment = StringHelper::concatenate(tokens, tokens.begin() + 6, tokens.end());

	Product* product = new Product(name, manufacturer, unit, expiryDate, entryDate, quantity, location, comment);
	section->addToSectionProducts(product);

	cout << ADDED_PRODUCT_SUCCESS_MESSAGE << endl;

	return product;
}

// private method
unsigned int Warehouse::removeProduct(Product* product, unsigned int quantityToRemove) {
	string productName = product->getName();
	ProductLocation location = product->getLocation();
	unsigned int productAvailableQuantity = product->getAvailableQuantity();

	// checks if there are enough products to be removed
	if (productAvailableQuantity > quantityToRemove) {
		unsigned int newQuantity = productAvailableQuantity - quantityToRemove;

		product->setAvailableQuantity(newQuantity);
	}
	else {
		cout << REMOVE_ALL_QUESTION << productAvailableQuantity << EXPIRING_ON << product->getExpiryDate() << YES_NO;
		// if there are less products than wanted to be removed, the user is asked if he still wants to remove what is left of that product
		string wantToRemove;
		cin >> wantToRemove;
		cin.ignore();

		if (wantToRemove == NO_ANSWER) {
			// if the user refuses to remove the left products, then nothing changes in the warehouse
			cout << NO_REMOVED_PRODUCTS_MESSAGE << product->getLocation() << endl;
			return 0;
		}

		quantityToRemove = productAvailableQuantity;
		this->sections[location.getSection()]->deleteFromSectionProducts(product);
	}

	cout << REMOVED << to_string(quantityToRemove) << SPACE_DELIMITER << productName << FROM << location << endl;
	return quantityToRemove;
}

unsigned int Warehouse::remove(string name, string quantityStr) {
	bool found = false;
	Section* section = nullptr;
	unsigned int removedQuantity = 0;

	// checks if a product with such name exists in the warehouse
	for (Section*& sect : this->sections) {
		if (sect->containsProductWithName(name)) {
			found = true;
			section = sect;
			break;
		}
	}

	if (!found) {
		cout << INEXISTENT_WAREHOUSE_PRODUCT_MESSAGE << endl;
		return removedQuantity;
	}

	unsigned int quantityToRemove = StringHelper::convertToInt(quantityStr);
	vector<Product*> products = section->getAllWithName(name);
	
	// if there is a single product with such name then a part of it or all of it is removed
	if (products.size() == 1) {
		removedQuantity = this->removeProduct(products[0], quantityToRemove);
		return removedQuantity;
	}

	section->sortByExpiryDate(products); // void function that sorts the given products by their expiry date in ascending order
	
	for (Product*& product : products) {
		removedQuantity = this->removeProduct(product, quantityToRemove);

		// checks if the given by the user quantity is removed
		if (removedQuantity == quantityToRemove) {
			return removedQuantity;
		}

		quantityToRemove -= removedQuantity;
	}

	return removedQuantity;
}

void Warehouse::clean() {
	Date today = DateHelper::getTodaysDate();

	for (Section*& section : this->sections) {
		for (Product*& product : section->getProducts()) {
			if (product->getExpiryDate() <= today) {
				cout << CLEANED << product->getAvailableQuantity() << SPACE_DELIMITER << product->getName() << SPACE_DELIMITER << product->getManufacturerName() << endl;

				section->deleteFromSectionProducts(product);
			}
		}
	}
}