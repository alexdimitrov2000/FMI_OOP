#pragma once
//#include <string>
#include "ProductLocation.h"

class Product  {
private:
	//std::string name;
	char* name;
	//Date expiryDate;
	//Date entryDate;
	char* manufacturerName;
	char* unit;
	unsigned int availableQuantity;
	ProductLocation location;
	char* comment;

public:
	Product();
	Product(const char* name, const char* manufacturerName, const char* unit, unsigned int availableQuantity, const ProductLocation& location, const char* comment);
	Product(const Product& other);
	Product& operator=(const Product& other);
	~Product();

	char* getName() const;
	char* getManufacturerName() const;
	char* getUnit() const;
	unsigned int getAvailableQuantity() const;
	ProductLocation getLocation() const;
	char* getComment() const;

	void setName(const char* name);
	void setManufacturerName(const char* manufacturerName);
	void setUnit(const char* unit);
	void setAvailableQuantity(const unsigned int quantity);
	void setLocation(const ProductLocation& location);
	void setComment(const char* comment);
};