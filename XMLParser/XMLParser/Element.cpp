#include <ostream>
#include <algorithm>
#include "Element.h"
#include "StringHelper.h"

Element::Element() : id(), tag(), attributes(), children(), content(), isTagSelfClosed(false), isElementClosed(false), numberOfParents(0) {}

Element::Element(const string& tag, bool isSelfClosed) : id(), tag(tag), attributes(), children(), content(), 
														 isTagSelfClosed(isSelfClosed), isElementClosed(false), numberOfParents(0) {}

Element::Element(const Element& other) : id(other.id), tag(other.tag), attributes(other.attributes), children(other.children), content(other.content), 
										 isTagSelfClosed(other.isTagSelfClosed), isElementClosed(other.isElementClosed), numberOfParents(other.numberOfParents) {}

Element& Element::operator=(const Element& other) {
	if (this != &other) {
		this->id = other.id;
		this->tag = other.tag;
		this->attributes = other.attributes;
		this->children = other.children;
		this->content = other.content;
		this->isTagSelfClosed = other.isTagSelfClosed;
		this->isElementClosed = other.isElementClosed;
		this->numberOfParents = other.numberOfParents;
	}

	return *this;
}

Element::~Element() {
	for (Attribute*& attr : this->attributes) {
		delete attr;
	}
	this->attributes.clear();

	for (Element*& child : this->children) {
		delete child;
	}
	this->children.clear();

	this->id.clear();
	this->tag.clear();
	this->content.clear();
}

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

unsigned int Element::getNumberOfParents() const {
	return this->numberOfParents;
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
		this->content += ' ';
	}

	this->content += content;
}

void Element::setIsSelfClosed(bool isTagSelfClosed) {
	this->isTagSelfClosed = isTagSelfClosed;
}

void Element::setIsClosed(bool isClosed) {
	this->isElementClosed = isClosed;
}

void Element::setNumberOfParents(unsigned int numberOfParents) {
	this->numberOfParents = numberOfParents;
}

void Element::addAttribute(Attribute*& attr) {
	this->attributes.push_back(attr);
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
		output << StringHelper::indent(child->getNumberOfParents()) << (*child);
	}

	if (element.content != "")
	{
		output << StringHelper::indent(element.getNumberOfParents() + 1) << element.content << endl;
	}

	output << StringHelper::indent(element.getNumberOfParents()) << "</" << element.tag << '>' << endl;

	return output;
}

bool Element::hasAttribute(const string& key) {
	return count_if(this->attributes.begin(), this->attributes.end(), [key](Attribute* a) {return a->getName() == key; }) == 1;
}

Attribute* Element::getAttributeByKey(const string& key) {
	vector<Attribute*>::iterator attr = find_if(this->attributes.begin(), this->attributes.end(), [key](Attribute* a) {return a->getName() == key; });

	return *attr;
}

void Element::deleteAttributeByKey(const string& key) {
	vector<Attribute*>::iterator attr = find_if(this->attributes.begin(), this->attributes.end(), [key](Attribute* a) {return a->getName() == key; });
	
	delete (*attr);
	this->attributes.erase(attr);
}