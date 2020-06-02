#pragma once
#include <iostream>
#include <vector>
#include <regex>
#include "Element.h"
#include "StringHelper.h"

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