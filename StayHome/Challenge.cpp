#include <cstring>
#include "Challenge.h"

void Challenge::copyObj(const char* tag, ChallengeStatus status, float rating, unsigned short int sendings, unsigned short int finishes) {
	strcpy_s(this->tag, strlen(tag) + 1, tag);
	this->status = status;
	this->rating = rating;
	this->sendingsCnt = sendings;
	this->finishesCnt = finishes;
}

Challenge::Challenge() : tag(""), status(ChallengeStatus::New), rating(0.0), sendingsCnt(0), finishesCnt(0) {}

Challenge::Challenge(const char* tag) : status(ChallengeStatus::New), rating(0.0), sendingsCnt(0), finishesCnt(0) {
	strcpy_s(this->tag, strlen(tag) + 1, tag);
}

Challenge::Challenge(Word& tag) : status(ChallengeStatus::New), rating(0.0), sendingsCnt(0), finishesCnt(0) {
	strcpy_s(this->tag, strlen(tag.getCharacters()) + 1, tag.getCharacters());
}

Challenge::Challenge(const Challenge& other) {
	this->copyObj(other.tag, other.status, other.rating, other.sendingsCnt, other.finishesCnt);
}

Challenge& Challenge::operator=(const Challenge& other) {
	if (this != &other) {
		this->copyObj(other.tag, other.status, other.rating, other.sendingsCnt, other.finishesCnt);
	}

	return *this;
}

bool Challenge::operator==(const char* tag) {
	return strcmp(this->tag, tag) == 0;
}

bool Challenge::operator==(Word& tag) {
	return strcmp(this->tag, tag.getCharacters()) == 0;
}

bool Challenge::operator==(const Challenge& other) {
	return strcmp(this->tag, other.tag) == 0;
}

char* Challenge::getTag() {
	return this->tag;
}

ChallengeStatus Challenge::getStatus() {
	return this->status;
}

float Challenge::getRating() const {
	return this->rating;
}

unsigned short int Challenge::getNumberOfSendings() const {
	return this->sendingsCnt;
}

unsigned short int Challenge::getNumberOfFinishes() const {
	return this->finishesCnt;
}

void Challenge::setTag(const char* tag) {
	strcpy_s(this->tag, strlen(tag) + 1, tag);
}

void Challenge::setStatus(ChallengeStatus status) {
	this->status = status;
}

void Challenge::setRating(float rating) {
	this->rating = rating;
}

void Challenge::increaseSendings() {
	this->sendingsCnt++;
}

void Challenge::increaseFinishes() {
	this->finishesCnt++;
}