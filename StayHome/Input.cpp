#include <iostream>
#include "Input.h"

Input::Input() : data(""), size(0), capacity(0), words(nullptr) {}

Input::Input(const char* data) : size(0), capacity(0), words(nullptr) {
	strcpy_s(this->data, strlen(data) + 1, data);
}

Input::Input(size_t initialCapacity) : data(""), size(0), capacity(initialCapacity) {
	this->words = new Word[this->capacity];
}

Input::Input(const char* data, size_t initialCapacity) : size(0), capacity(initialCapacity) {
	strcpy_s(this->data, strlen(data) + 1, data);
	this->words = new Word[this->capacity];
}

Input::Input(const Input& other) {
	this->copyObj(other);
}

Input& Input::operator=(const Input& other) {
	if (this != &other) {
		this->erase();
		this->copyObj(other);
	}

	return *this;
}

Input::~Input() {
	this->erase();
}

void Input::copyObj(const Input& other) {
	strcpy_s(this->data, strlen(other.data) + 1, other.data);
	this->size = other.size;
	this->capacity = other.capacity;
	this->words = new Word[this->capacity];
	for (size_t i = 0; i < other.capacity; i++)
	{
		this->words[i] = other.words[i];
	}
}

void Input::erase() {
	delete[] this->words;
}

void Input::resize() {
	if (this->capacity <= 0) {
		this->capacity = 3;
		this->words = new Word[this->capacity];
		return;
	}

	this->capacity *= 2;
	Word* newWordCollection = new Word[this->capacity];

	for (size_t i = 0; i < this->size; i++)
	{
		newWordCollection[i] = this->words[i];
	}

	delete[] this->words;
	this->words = newWordCollection;
}

void Input::addWord(const Word& token) {
	if (this->size >= this->capacity)
	{
		this->resize();
	}

	this->words[this->size] = token;
	this->size++;
}

void Input::getWord(int startIndex, int endIndex) {
	char word[30];
	int index = 0;

	for (int i = startIndex; i < endIndex; i++)
	{
		word[index] = this->data[i];
		index++;
	}
	word[index] = '\0';

	this->addWord(Word(word));
}

void Input::split() {
	int lastSpaceIndex = 0;

	for (int i = 1; this->data[i] != '\0'; i++)
	{
		if (this->data[i] == ' ') {
			getWord(lastSpaceIndex, i);
			lastSpaceIndex = i + 1;
		}
	}
	getWord(lastSpaceIndex, strlen(this->data));
}

Word Input::getCommand() const {
	return this->words[0];
}

Word* Input::getTokens() const {
	return this->words + 1;
}

size_t Input::getSize() const {
	return this->size;
}

size_t Input::getTokensCnt() const {
	return this->size - 1;
}