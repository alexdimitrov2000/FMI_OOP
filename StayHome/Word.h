#pragma once

const int MAX_WORD_LENGTH = 30;

class Word {
private:
	char characters[MAX_WORD_LENGTH];

public:
	Word();
	Word(const char* characters);
	Word& operator=(const Word& other);
	bool operator==(const Word& other);
	bool operator==(const char* characters);
	bool operator!=(const Word& other);
	bool operator!=(const char* characters);

	char* getCharacters();
	void setCharacters(const char* chars);

	int getLength();
};