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