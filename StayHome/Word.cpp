#include <cstring>
#include "Word.h"

Word::Word() : characters("") {}

Word::Word(const char* characters) {
	strcpy_s(this->characters, strlen(characters) + 1, characters);
}

Word& Word::operator=(const Word& other) {
	if (this != &other) {
		strcpy_s(this->characters, strlen(other.characters) + 1, other.characters);
	}

	return *this;
}

bool Word::operator==(const Word& other) {
	return strcmp(this->characters, other.characters) == 0;
}

bool Word::operator==(const char* characters) {
	return strcmp(this->characters, characters) == 0;
}

bool Word::operator!=(const Word& other) {
	return strcmp(this->characters, other.characters) != 0;
}

bool Word::operator!=(const char* characters) {
	return strcmp(this->characters, characters) != 0;
}

char* Word::getCharacters() {
	return this->characters;
}

void Word::setCharacters(const char* chars) {
	strcpy_s(this->characters, strlen(chars) + 1, chars);
}

int Word::getLength() {
	int i;
	for (i = 0; this->characters[i] != '\0'; i++) {}

	return i;
}