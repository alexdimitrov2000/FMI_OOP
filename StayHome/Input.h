#pragma once
#include "Word.h"

const int INPUT_MAX_LENGTH = 200;

class Input {
private:
	size_t size;
	size_t capacity;
	char data[INPUT_MAX_LENGTH];
	Word* words;

	void copyObj(const Input& other);
	void erase();
	void resize();
	void addWord(const Word& word);
	void getWord(int startIndex, int endIndex);
public:
	Input();
	Input(const char* data);
	Input(size_t initialCapacity);
	Input(const char* data, size_t initialCapacity);
	Input(const Input& other);
	Input& operator=(const Input& other);
	~Input();

	void split();

	Word getCommand() const;
	Word* getTokens() const;
	size_t getSize() const;
	size_t getTokensCnt() const;
};