#pragma once
#include <iostream>
#include <vector>
#include "Element.h"
#include "StringHelper.h"

class XmlParser {
private:
	Element* rootElement;
	vector<Element*> elements;
	vector<Element*> openedElements;
	vector<string> ids;

	Element* constructElement(const string& line);
	string generateId(const string& id);
	int getNumberOfElementsWithId(const string& currentId);
	Element* getElementById(const string& id);
public:
	XmlParser();

	void parse(const vector<string>& fileContent);
	void print();
	void selectElementAttr(const string& id, const string& key);
	void setElementAttrValue(const string& id, const string& key, const string& value);
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
	Element element;
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
		element.setTag(match[1]);

		if (element.getTag()[0] == '/') {
			this->openedElements.back()->setIsClosed(true);
			return this->openedElements.back();
		}
	}

	string::const_iterator iterator = line.cbegin();
	while (regex_search(iterator, line.cend(), match, attributeRgx)) {
		if (match[1] == "id") {
			elementId = this->generateId(match[2]);
			
			element.setId(elementId);
		}
		else {
			Attribute attr(match[1], match[2]);
			element.addAttribute(attr);
		}

		iterator = match.suffix().first;
	}

	if (elementId == "") {
		elementId = this->generateId(elementId);

		element.setId(elementId);
	}

	if (regex_search(line, match, contentRgx)) {
		element.addContent(match[1]);
	}

	if (regex_match(line, closingTagRgx)) {
		element.setIsClosed(true);
	}
	else if (regex_match(line, selfClosingTagRgx)) {
		element.setIsSelfClosed(true);
	}

	this->ids.push_back(elementId);

	return new Element(element);
}

void XmlParser::parse(const vector<string>& fileContent) {
	string currentLine;
	size_t linesCnt = fileContent.size();

	for (size_t i = 0; i < linesCnt; i++)
	{
		currentLine = StringHelper::trim(fileContent[i]);
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
		else {
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
		cout << "There is no element with such ID" << endl;
		return;
	}

	if (!element->hasAttribute(key)) {
		cout << "There is no such attribute" << endl;
		return;
	}

	Attribute& attr = element->getAttributeByKey(key);

	cout << attr.getValue() << endl;
}

void XmlParser::setElementAttrValue(const string& id, const string& key, const string& value) {
	Element* element = this->getElementById(id);

	if (element == nullptr) {
		cout << "There is no element with such ID" << endl;
		return;
	}

	if (!element->hasAttribute(key)) {
		Attribute attr(key, value);
		element->addAttribute(attr);
		return;
	}

	element->getAttributeByKey(key).setValue(value);
}