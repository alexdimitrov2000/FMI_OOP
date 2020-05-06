#include "Attribute.h"

Attribute::Attribute() : name(), value() {}

Attribute::Attribute(const string& name, const string& value) : name(name), value(value) {}

Attribute& Attribute::operator=(const Attribute& other) {
	if (this != &other)
	{
		this->name = other.name;
		this->value = other.value;
	}

	return *this;
}

string Attribute::getName() const {
	return this->name;
}

string Attribute::getValue() const {
	return this->value;
}

void Attribute::setName(const string& name) {
	this->name = name;
}

void Attribute::setValue(const string& value) {
	this->value = value;
}

//ostream& operator<<(ostream& output, const Attribute& attr) {
//	return output;
//}