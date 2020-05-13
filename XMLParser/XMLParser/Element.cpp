#include <ostream>
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

vector<Attribute> Element::getAttributes() const {
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

void Element::setContent(const string& content) {
	this->content = content;
}

void Element::setIsSelfClosed(bool isTagSelfClosed) {
	this->isTagSelfClosed = isTagSelfClosed;
}

void Element::setIsClosed(bool isClosed) {
	this->isElementClosed = isClosed;
}

void Element::addAttribute(const Attribute& attr) {
	this->attributes.push_back(attr);
}

void Element::addChildElement(Element*& element) {
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

	if (element.isTagSelfClosed)
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