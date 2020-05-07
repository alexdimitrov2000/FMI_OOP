#include <iostream>
#include "Input.h"

Input::Input() : data(), words() {}

Input::Input(const string& data) : data(data), words() {}

Input::Input(const Input& other) {
	this->copyObj(other);
}

Input& Input::operator=(const Input& other) {
	if (this != &other) {
		this->copyObj(other);
	}

	return *this;
}

void Input::copyObj(const Input& other) {
	this->data = other.data;
	this->words = other.words;
}

void Input::getWord(int startIndex, int endIndex) {
	string word;

	for (int i = startIndex; i < endIndex; i++)
	{
		word += this->data[i];
	}

	this->words.push_back(word);
}

void Input::split() {
	int lastSpaceIndex = 0;
	int dataLength = this->data.size();

	for (int i = 0; i < dataLength; i++)
	{
		if (this->data[i] == ' ') {
			getWord(lastSpaceIndex, i);
			lastSpaceIndex = i + 1;
		}
	}
	getWord(lastSpaceIndex, dataLength);
}

void Input::clearData() {
	this->data.clear();
	this->words.clear();
}

vector<string> Input::getTokens() const {
	return this->words;
}

void Input::setData(const string& data) {
	this->data = data;
}