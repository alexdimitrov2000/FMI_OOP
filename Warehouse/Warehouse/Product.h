#pragma once
#include <string>
#include "ProductLocation.h"

using namespace std;

class Product  {
private:
	string name;
	//Date expiryDate;
	//Date entryDate;
	string manufacturerName;
	string unit;
	unsigned int availableQuantity;
	ProductLocation location;
	string comment;

public:
	Product();
	Product(const string& name, const string& manufacturerName, const string& unit, unsigned int availableQuantity, const ProductLocation& location, const string& comment);
	Product(const Product& other);
	Product& operator=(const Product& other);
	~Product();

	string getName() const;
	string getManufacturerName() const;
	string getUnit() const;
	unsigned int getAvailableQuantity() const;
	ProductLocation getLocation() const;
	string getComment() const;

	void setName(const string& name);
	void setManufacturerName(const string& manufacturerName);
	void setUnit(const string& unit);
	void setAvailableQuantity(const unsigned int quantity);
	void setLocation(const ProductLocation& location);
	void setComment(const string& comment);
};