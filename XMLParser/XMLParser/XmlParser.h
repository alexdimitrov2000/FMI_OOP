#pragma once
#include <iostream>
#include <vector>
#include "Element.h"
#include "StringHelper.h"

class XmlParser {
private:
	Element* rootElement;
	vector<Element*> openedElements;

	Element* constructElement(const string& line);
public:
	XmlParser();

	void parse(const vector<string>& fileContent);
};

XmlParser::XmlParser() : rootElement() {}

Element* XmlParser::constructElement(const string& line) {
	Element element;
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
		Attribute attr(match[1], match[2]);
		element.addAttribute(attr);

		iterator = match.suffix().first;
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

		//cout << currentLine << endl;
	}

	cout << (*this->rootElement) << endl;
}