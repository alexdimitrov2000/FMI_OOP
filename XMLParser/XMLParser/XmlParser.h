#pragma once
#include <iostream>
#include <vector>
#include "Element.h"
#include "StringHelper.h"

// Operation messages
const char NO_ELEMENT_WITH_SUCH_ID_MESSAGE[] = "There is no element with such ID.";
const char ATTR_NOT_FOUND_MESSAGE[] = "There is no such attribute.";
const char NO_CHILD_ATTRS_MESSAGE[] = "Element's children have no attributes.";
const char CHILD_AT_INDEX_NOT_FOUND_MESSAGE[] = "Child at this index was not found.";
const char ATTR_VALUE_SET_MESSAGE[] = "Attribute value was set.";
const char DELETE_ATTR_SUCCESS_MESSAGE[] = "Attribute was deleted successfully.";
const char ID_ATTR_CANNOT_BE_DELETED_MESSAGE[] = "You cannot delete the ID attribute.";
const char CHILD_ADDED_MESSAGE[] = "The child was added.";

class XmlParser {
private:
	Element* rootElement;
	vector<Element*> elements;
	vector<Element*> openedElements;
	vector<string> ids;

	Element* constructElement(const string& line);
	string generateId(const string& id = "");
	int getNumberOfElementsWithId(const string& currentId);
	Element* getElementById(const string& id);
public:
	XmlParser();

	Element* getRootElement();
	void clearData();

	void parse(const vector<string>& fileContent);
	void print();
	void selectElementAttr(const string& id, const string& key);
	void setElementAttrValue(const string& id, const string& key, const string& value);
	vector<Attribute*> getChildrenAttributes(const string& id);
	Element* getNthChild(const string& id, const string& n);
	string getContent(const string& id);
	void deleteElementAttr(const string& id, const string& key);
	void addChildToElement(const string& id, const string& childTag);
};

XmlParser::XmlParser() : rootElement(), elements(), openedElements(), ids() {}


int XmlParser::getNumberOfElementsWithId(const string& id) {
	return count_if(this->ids.begin(), this->ids.end(), [id](string i) { return i == id; });
}

Element* XmlParser::getElementById(const string& id) {
	if (this->getNumberOfElementsWithId(id) == 0) {
		return nullptr;
	}

	vector<Element*>::iterator element = find_if(this->elements.begin(), this->elements.end(), [id](Element* e) {return e->getId() == id; });

	return *element;
}

string XmlParser::generateId(const string& currentId) {
	string id = currentId;
	smatch match;
	regex idRegex("(\\d+)_?\\d*");

	if (id == "" && this->ids.empty()) {
		id = "1";
	}
	else if (id == "" && regex_search(this->ids.back(), match, idRegex)) {
		id = to_string(StringHelper::convertToInt(match[1]) + 1);
	}

	int elementsWithIdCnt = this->getNumberOfElementsWithId(id);

	if (elementsWithIdCnt > 0) {
		id += ("_" + to_string(elementsWithIdCnt));
	}

	return id;
}

Element* XmlParser::constructElement(const string& line) {
	Element* element = new Element();
	string elementId;
	regex tagNameRgx("<([\/a-zA-Z-_]+).*>");
	regex attributeRgx("([a-zA-Z-_]+)=\"([a-zA-Z0-9 .]+)\"");
	regex closingTagRgx(".+<\/([a-zA-Z-_]+)>");
	regex selfClosingTagRgx(".*\/>");
	regex contentRgx(">(.*)<\/");
	regex isContentLine("[^<>]+");
	smatch match;

	if (regex_match(line, isContentLine)) {
		this->openedElements.back()->addContent(line);

		return nullptr;
	}

	if (regex_search(line, match, tagNameRgx)) {
		element->setTag(match[1]);

		if (element->getTag()[0] == '/') {
			this->openedElements.back()->setIsClosed(true);
			return this->openedElements.back();
		}
	}

	string::const_iterator iterator = line.cbegin();
	while (regex_search(iterator, line.cend(), match, attributeRgx)) {
		if (match[1] == "id") {
			elementId = this->generateId(match[2]);
			
			element->setId(elementId);
		}
		else {
			Attribute attr(match[1], match[2]);
			element->addAttribute(attr);
		}

		iterator = match.suffix().first;
	}

	if (elementId == "") {
		elementId = this->generateId();

		element->setId(elementId);
	}

	if (regex_search(line, match, contentRgx)) {
		element->addContent(match[1]);
	}

	if (regex_match(line, closingTagRgx)) {
		element->setIsClosed(true);
	}
	else if (regex_match(line, selfClosingTagRgx)) {
		element->setIsSelfClosed(true);
	}

	this->ids.push_back(elementId);

	return element;
}

Element* XmlParser::getRootElement() {
	return this->rootElement;
}

void XmlParser::clearData() {
	this->elements.clear();
	this->ids.clear();
	this->openedElements.clear();
	delete this->rootElement;
	this->rootElement = nullptr;
}

void XmlParser::parse(const vector<string>& fileContent) {
	string currentLine;
	size_t linesCnt = fileContent.size();

	for (size_t i = 0; i < linesCnt; i++)
	{
		currentLine = StringHelper::trim(fileContent[i]);

		if (currentLine == "") {
			continue;
		}

		Element* element = this->constructElement(currentLine);

		if (element == nullptr) {
			continue;
		}
		else if (this->openedElements.size() > 0 && element == this->openedElements.back()) {
			this->openedElements.pop_back();
			continue;
		}

		if (this->openedElements.size() > 0) {
			this->openedElements.back()->addChildElement(element);
		}
		else if (this->rootElement == nullptr) {
			this->rootElement = element;
		}

		if (!element->isSelfClosed() && !element->isClosed()) {
			this->openedElements.push_back(element);
		}

		this->elements.push_back(element);
	}
}

void XmlParser::print() {
	cout << (*this->rootElement);
}

void XmlParser::selectElementAttr(const string& id, const string& key) {
	Element* element = this->getElementById(id);

	if (element == nullptr) {
		cout << NO_ELEMENT_WITH_SUCH_ID_MESSAGE << endl;
		return;
	}

	if (!element->hasAttribute(key)) {
		cout << ATTR_NOT_FOUND_MESSAGE << endl;
		return;
	}

	Attribute* attr = element->getAttributeByKey(key);

	cout << attr->getValue() << endl;
}

void XmlParser::setElementAttrValue(const string& id, const string& key, const string& value) {
	Element* element = this->getElementById(id);

	if (element == nullptr) {
		cout << NO_ELEMENT_WITH_SUCH_ID_MESSAGE << endl;
		return;
	}

	if (!element->hasAttribute(key)) {
		Attribute attr(key, value);
		element->addAttribute(attr);
		cout << ATTR_VALUE_SET_MESSAGE << endl;
		return;
	}

	element->getAttributeByKey(key)->setValue(value);
	cout << ATTR_VALUE_SET_MESSAGE << endl;
}

vector<Attribute*> XmlParser::getChildrenAttributes(const string& id) {
	Element* element = this->getElementById(id);
	vector<Attribute*> attrs;

	if (element == nullptr) {
		cout << NO_ELEMENT_WITH_SUCH_ID_MESSAGE << endl;
		return attrs;
	}

	vector<Element*> children = element->getChildren();
	
	for (Element*& child : children) {
		for (Attribute*& attr : child->getAttributes()) {
			attrs.push_back(attr);
		}
	}

	if (attrs.size() == 0) {
		cout << NO_CHILD_ATTRS_MESSAGE << endl;
	}

	return attrs;
}

Element* XmlParser::getNthChild(const string& id, const string& n) {
	Element* element = this->getElementById(id);

	if (element == nullptr) {
		cout << NO_ELEMENT_WITH_SUCH_ID_MESSAGE << endl;
		return nullptr;
	}

	int index = StringHelper::convertToInt(n);
	vector<Element*> children = element->getChildren();

	if (index < 0 || index >= children.size()) {
		cout << CHILD_AT_INDEX_NOT_FOUND_MESSAGE << endl;
		return nullptr;
	}

	return children[index];
}

string XmlParser::getContent(const string& id) {
	Element* element = this->getElementById(id);

	return element->getContent();
}

void XmlParser::deleteElementAttr(const string& id, const string& key) {
	Element* element = this->getElementById(id);

	if (element == nullptr) {
		cout << NO_ELEMENT_WITH_SUCH_ID_MESSAGE << endl;
		return;
	}

	if (key == "id") {
		cout << ID_ATTR_CANNOT_BE_DELETED_MESSAGE << endl;
		return;
	}
	else if (!element->hasAttribute(key)) {
		cout << ATTR_NOT_FOUND_MESSAGE << endl;
		return;
	}

	element->deleteAttributeByKey(key);

	cout << DELETE_ATTR_SUCCESS_MESSAGE << endl;
}

void XmlParser::addChildToElement(const string& id, const string& childTag) {
	Element* element = this->getElementById(id);

	if (element == nullptr)
	{
		cout << NO_ELEMENT_WITH_SUCH_ID_MESSAGE << endl;
		return;
	}

	Element* child = new Element(childTag);
	string childId = this->generateId();
	child->setId(childId);

	element->addChildElement(child);
	
	this->elements.push_back(child);
	this->ids.push_back(childId);

	cout << CHILD_ADDED_MESSAGE << endl;
}