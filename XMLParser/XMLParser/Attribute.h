#pragma once
#include <string>
using namespace std;

class Attribute {
private:
	string name;
	string value;

public:
	Attribute();
	Attribute(const string& name, const string& value);
	Attribute(const Attribute& other);
	Attribute& operator=(const Attribute& other);

	string getName() const;
	string getValue() const;

	void setName(const string& name);
	void setValue(const string& value);

	//friend ostream& operator<<(ostream& output, const Attribute& attr);
};