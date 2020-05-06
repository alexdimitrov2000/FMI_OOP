#pragma once
#include <vector>
#include "Attribute.h"

class Element {
private:
	string id;
	string tag;
	vector<Attribute> attributes;
	vector<Element> children;
	string content;
	bool isSelfClosed;

public:
	Element();
	Element(const string& tag, bool isTagSelfClosed = false);

	string getId() const;
	string getTag() const;
	vector<Attribute> getAttributes() const;
	vector<Element> getChildren() const;
	string getContent() const;
	bool isTagSelfClosed() const;

	void setId(const string& id);
	void setTag(const string& tag);
	void setContent(const string& content);
	void setIsTagSelfClosed(bool isTagSelfClosed);

	void addAttribute(const Attribute& attr);
	void addChildElement(const Element& element);

	friend ostream& operator<<(ostream& output, const Element& element);
};

Element::Element() : id(), tag(), attributes(), children(), content(), isSelfClosed(false) {}

Element::Element(const string& tag, bool isTagSelfClosed) : id(), tag(tag), attributes(), children(), content(), isSelfClosed(isTagSelfClosed) {}

string Element::getId() const {
	return this->id;
}

string Element::getTag() const {
	return this->tag;
}

vector<Attribute> Element::getAttributes() const {
	return this->attributes;
}

vector<Element> Element::getChildren() const {
	return this->children;
}

string Element::getContent() const {
	return this->content;
}

bool Element::isTagSelfClosed() const {
	return this->isSelfClosed;
}

void Element::setId(const string& id) {
	this->id = id;
}

void Element::setTag(const string& tag) {
	this->tag = tag;
}

void Element::setContent(const string& content) {
	this->content = content;
}

void Element::setIsTagSelfClosed(bool isTagSelfClosed) {
	this->isSelfClosed = isTagSelfClosed;
}

void Element::addAttribute(const Attribute& attr) {
	this->attributes.push_back(attr);
}

void Element::addChildElement(const Element& element) {
	this->children.push_back(element);
}

ostream& operator<<(ostream& output, const Element& element) {
	output << '<' << element.tag << ' ';
	int attrsCnt = element.attributes.size();
	int childrenCnt = element.children.size();

	Attribute currentAttr;
	for (size_t i = 0; i < attrsCnt; i++)
	{
		currentAttr = element.attributes[i];
		output << currentAttr.getName() << "=\"" << currentAttr.getValue() << "\" ";
	}

	if (element.isTagSelfClosed())
	{
		output << "/>" << endl;
		return output;
	}

	output << '>' << endl;

	if (childrenCnt != 0)
	{
		for (size_t i = 0; i < childrenCnt; i++)
		{
			output << element.children[i];
		}
	}
	
	if (element.content != "")
	{
		output << element.content << endl;
	}

	output << "</" << element.tag << '>' << endl;

	return output;
}