#pragma once
#include <iostream>
#include <vector>
#include "Element.h"
#include "StringHelper.h"

class XmlParser {
private:
	vector<Element> elements;

	Element constructElement(const string& line);
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

Element XmlParser::constructElement(const string& line) {
	Element element;
	regex tagNameRgx("<([\/a-zA-Z-_]+).*>");
	regex attributeRgx("([a-zA-Z-_]+)=\"([a-zA-Z0-9 .]+)\"");
	regex selfClosingTagRgn(".*\/>");
	smatch match;

	vector<string> tokens;
	if (regex_search(line, match, tagNameRgx)) {
		tokens.push_back(match[1]);
		element.setTag(match[1]);

		if (element.getTag()[0] == '/') {
			return element;
		}
	}

	string::const_iterator iterator = line.cbegin();
	while (regex_search(iterator, line.cend(), match, attributeRgx)) {
		tokens.push_back(match[0]);

		Attribute attr(match[1], match[2]);
		element.addAttribute(attr);
		
		iterator = match.suffix().first;
	}

	if (regex_match(line, selfClosingTagRgn)) {
		element.setIsTagSelfClosed(true);
	}

	return element;
}

void XmlParser::parse(const vector<string>& fileContent) {
	string currentLine;
	int linesCnt = fileContent.size();
	Input input;

	for (size_t i = 0; i < linesCnt; i++)
	{
		currentLine = trim(fileContent[i]);
		Element element = this->constructElement(currentLine);
		this->elements.push_back(element);

		cout << currentLine << endl;
	}
		cout << this->elements[1] << endl;
		cout << this->elements[3] << endl;
}