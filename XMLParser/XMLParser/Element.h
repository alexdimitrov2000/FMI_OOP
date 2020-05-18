#pragma once
#include <vector>
#include "Attribute.h"

class Element {
private:
	string id;
	string tag;
	vector<Attribute*> attributes;
	vector<Element*> children;
	string content;
	bool isTagSelfClosed;
	bool isElementClosed;

public:
	Element();
	Element(const string& tag, bool isSelfClosed = false);
	Element(const Element& other);

	string getId() const;
	string getTag() const;
	vector<Attribute*> getAttributes() const;
	vector<Element*> getChildren() const;
	string getContent() const;
	bool isSelfClosed() const;
	bool isClosed() const;

	void setId(const string& id);
	void setTag(const string& tag);
	void addContent(const string& content, bool trunc = false);
	void setIsSelfClosed(bool isSelfClosed);
	void setIsClosed(bool isClosed);

	void addAttribute(const Attribute& attr);
	void addChildElement(Element*& element);

	bool hasAttribute(const string& key);
	Attribute* getAttributeByKey(const string& key);

	friend ostream& operator<<(ostream& output, const Element& element);
};