#pragma once
#include <iostream>
#include <vector>
#include "Element.h"
#include "StringHelper.h"

class XmlParser {
private:
	vector<Element*> elements;
	vector<Element*> openedElements;

	Element* constructElement(const string& line);
public:
	XmlParser();

	void parse(const vector<string>& fileContent);
};

XmlParser::XmlParser() : elements() {}

string trim(const string& line) {
	regex rgx("^\s*(.+)");
	smatch match;
	if (regex_search(line, match, rgx)) {
		return match[1];
	}

	return line;
}

Element* XmlParser::constructElement(const string& line) {
	Element element;
	regex tagNameRgx("<([\/a-zA-Z-_]+).*>");
	regex attributeRgx("([a-zA-Z-_]+)=\"([a-zA-Z0-9 .]+)\"");
	regex closingTagRgx(".+<\/([a-zA-Z-_]+)>");
	regex selfClosingTagRgx(".*\/>");
	regex contentRgx(">(.*)<\/");
	smatch match;

	if (regex_search(line, match, tagNameRgx)) {
		element.setTag(match[1]);

		if (element.getTag()[0] == '/') {
			element.setIsClosed(true);
			return new Element(element);
		}
	}

	string::const_iterator iterator = line.cbegin();
	while (regex_search(iterator, line.cend(), match, attributeRgx)) {
		Attribute attr(match[1], match[2]);
		element.addAttribute(attr);

		iterator = match.suffix().first;
	}

	if (regex_search(line, match, contentRgx)) {
		element.setContent(match[1]);
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
	int linesCnt = fileContent.size();

	for (size_t i = 0; i < linesCnt; i++)
	{
		currentLine = trim(fileContent[i]);
		Element* element = this->constructElement(currentLine);

		if (this->openedElements.size() != 0) {
			(*this->openedElements.back()).addChildElement(element);
		}
		else {
			this->elements.push_back(element);
		}

		if (!(*element).isSelfClosed() && !(*element).isClosed()) {
			this->openedElements.push_back(element);
		}
		else if ((*element).isClosed() && (*element).getId() == (*this->openedElements.back()).getId()) {
			this->openedElements.pop_back();
		}

		cout << currentLine << endl;
	}
	cout << this->elements[1] << endl;
	cout << this->elements[3] << endl;
}