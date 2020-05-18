#include <ostream>
#include <algorithm>
#include "Element.h"

Element::Element() : id(), tag(), attributes(), children(), content(), isTagSelfClosed(false), isElementClosed(false) {}

Element::Element(const string& tag, bool isSelfClosed) : id(), tag(tag), attributes(), children(), content(), isTagSelfClosed(isSelfClosed), isElementClosed(false) {}

Element::Element(const Element& other) : id(other.id), tag(other.tag), attributes(other.attributes),
										 children(other.children), content(other.content), isTagSelfClosed(other.isTagSelfClosed), isElementClosed(other.isElementClosed) {}

string Element::getId() const {
	return this->id;
}

string Element::getTag() const {
	return this->tag;
}

vector<Attribute*> Element::getAttributes() const {
	return this->attributes;
}

vector<Element*> Element::getChildren() const {
	return this->children;
}

string Element::getContent() const {
	return this->content;
}

bool Element::isSelfClosed() const {
	return this->isTagSelfClosed;
}

bool Element::isClosed() const {
	return this->isTagSelfClosed || this->isElementClosed;
}

void Element::setId(const string& id) {
	this->id = id;
}

void Element::setTag(const string& tag) {
	this->tag = tag;
}

void Element::addContent(const string& content, bool trunc) {
	if (trunc) {
		this->content = content;
		return;
	}

	if (this->content != "") {
		this->content += '\n';
	}

	this->content += content;
}

void Element::setIsSelfClosed(bool isTagSelfClosed) {
	this->isTagSelfClosed = isTagSelfClosed;
}

void Element::setIsClosed(bool isClosed) {
	this->isElementClosed = isClosed;
}

void Element::addAttribute(const Attribute& attr) {
	this->attributes.push_back(new Attribute(attr));
}

void Element::addChildElement(Element*& element) {
	this->children.push_back(element);
}

ostream& operator<<(ostream& output, const Element& element) {
	output << '<' << element.tag;

	output << " id=\"" << element.getId() << '"';

	for (Attribute* attr : element.attributes) {
		output << (*attr);
	}

	if (element.isTagSelfClosed)
	{
		output << " />" << endl;
		return output;
	}

	output << '>' << endl;

	for (Element* child : element.children) {
		output << (*child);
	}

	if (element.content != "")
	{
		output << element.content << endl;
	}

	output << "</" << element.tag << '>' << endl;

	return output;
}

bool Element::hasAttribute(const string& key) {
	return count_if(this->attributes.begin(), this->attributes.end(), [key](Attribute* a) {return a->getName() == key; }) == 1;
}

Attribute* Element::getAttributeByKey(const string& key) {
	vector<Attribute*>::iterator attr = find_if(this->attributes.begin(), this->attributes.end(), [key](Attribute* a) {return a->getName() == key; });

	return *attr;
}