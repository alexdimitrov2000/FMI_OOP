#pragma once
#include <string>
#include "ProductLocation.h"
#include "Date.h"

using namespace std;

class Product  {
private:
	string name;
	string manufacturerName;
	string unit;
	Date expiryDate;
	Date entryDate;
	unsigned int availableQuantity;
	ProductLocation location;
	string comment;

public:
	Product();
	Product(const string& name, const string& manufacturerName, const string& unit, const Date& expiryDate, const Date& entryDate, unsigned int availableQuantity, const ProductLocation& location, const string& comment);
	Product(const Product& other);
	Product& operator=(const Product& other);
	~Product();

	string getName() const;
	string getManufacturerName() const;
	string getUnit() const;
	Date getExpiryDate() const;
	Date getEntryDate() const;
	unsigned int getAvailableQuantity() const;
	ProductLocation getLocation() const;
	string getComment() const;

	void setName(const string& name);
	void setManufacturerName(const string& manufacturerName);
	void setUnit(const string& unit);
	void setExpiryDate(const Date& expiryDate);
	void setEntryDate(const Date& entryDate);
	void setAvailableQuantity(const unsigned int quantity);
	void setLocation(const ProductLocation& location);
	void setComment(const string& comment);

	friend ostream& operator<<(ostream& output, const Product& product);
};