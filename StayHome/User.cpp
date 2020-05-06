#include <cstring>
#include "User.h"

void User::erase() {
	delete[] this->name;
	delete[] this->unfulfilledChallenges;
}

User::User() : name(nullptr), email(""), age(0), id(0), unfulfilledChallenges(nullptr), challengesCnt(0), challengesCapacity(0) {}

User::User(const char* name) : email(""), age(0), id(0), unfulfilledChallenges(nullptr), challengesCnt(0), challengesCapacity(0) {
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
}

User::User(const char* name, int age) : age(age), email(""), id(0), unfulfilledChallenges(nullptr), challengesCnt(0), challengesCapacity(0) {
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
}

User::User(const char* name, const char* email) : age(0), id(0), unfulfilledChallenges(nullptr), challengesCnt(0), challengesCapacity(0) {
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);

	strcpy_s(this->email, strlen(email) + 1, email);
}

User::User(const char* name, int age, const char* email) {
	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
	this->age = age;
	strcpy_s(this->email, strlen(email) + 1, email);
	this->id = 0;
	this->unfulfilledChallenges = nullptr;
	this->challengesCnt = 0;
	this->challengesCapacity = 0;
}

User::User(const User& other) {
	this->name = new char[strlen(other.name) + 1];
	strcpy_s(this->name, strlen(other.name) + 1, other.name);
	this->age = other.age;
	strcpy_s(this->email, strlen(other.email) + 1, other.email);
	this->id = other.id;
	this->challengesCnt = other.challengesCnt;
	this->challengesCapacity = other.challengesCapacity;
	this->unfulfilledChallenges = other.unfulfilledChallenges;
}

User& User::operator=(const User& other) {
	if (this != &other) {
		this->erase();

		this->name = new char[strlen(other.name) + 1];
		strcpy_s(this->name, strlen(other.name) + 1, other.name);
		this->age = other.age;
		strcpy_s(this->email, strlen(other.email) + 1, other.email);
		this->id = other.id;
		this->challengesCnt = other.challengesCnt;
		this->challengesCapacity = other.challengesCapacity;
		this->unfulfilledChallenges = other.unfulfilledChallenges;
	}

	return *this;
}

bool User::operator==(const char* name) {
	return strcmp(this->name, name) == 0;
}

User::~User() {
	this->erase();
}

void User::resizeChallenges() {
	if (this->challengesCapacity <= 0) {
		this->challengesCapacity = 1;
		this->unfulfilledChallenges = new Challenge[this->challengesCapacity];
		return;
	}

	this->challengesCapacity *= 2;
	if (this->challengesCapacity > 65535) {
		this->challengesCapacity = 65535;
	}

	Challenge* newChallengeCollection = new Challenge[this->challengesCapacity];

	for (size_t i = 0; i < this->challengesCnt; i++)
	{
		newChallengeCollection[i] = this->unfulfilledChallenges[i];
	}

	delete[] this->unfulfilledChallenges;
	this->unfulfilledChallenges = newChallengeCollection;
}

int User::getChallengeIndex(const char* tag) {
	for (size_t i = 0; i < this->challengesCnt; i++)
	{
		if (this->unfulfilledChallenges[i] == tag) {
			return i;
		}
	}

	return -1;
}

char* User::getName() const {
	return this->name;
}

int User::getAge() const {
	return this->age;
}

char* User::getEmail() {
	return this->email;
}

unsigned int User::getId() const {
	return this->id;
}

Challenge* User::getChallenges() {
	return this->unfulfilledChallenges;
}

unsigned short int User::getNumberOfUnfulfilledChallenges() const {
	return this->challengesCnt;
}

bool User::containsChallenge(const char* tag) {
	for (size_t i = 0; i < this->challengesCnt; i++)
	{
		if (this->unfulfilledChallenges[i] == tag) {
			return true;
		}
	}

	return false;
}

void User::setName(const char* name) {
	delete[] this->name;

	this->name = new char[strlen(name) + 1];
	strcpy_s(this->name, strlen(name) + 1, name);
}

void User::setAge(int age) {
	this->age = age;
}

void User::setEmail(const char* email) {
	strcpy_s(this->email, strlen(email) + 1, email);
}

void User::setId(unsigned int id) {
	this->id = id;
}

bool User::hasAge() {
	return this->age != 0;
}

bool User::hasEmail() {
	return strcmp(this->email, "") != 0;
}

void User::addChallenge(Challenge& challenge) {
	if (this->containsChallenge(challenge.getTag())) {
		return;
	}

	if (this->challengesCnt >= this->challengesCapacity) {
		this->resizeChallenges();
	}

	this->unfulfilledChallenges[this->challengesCnt] = challenge;
	this->challengesCnt++;
}

void User::removeChallenge(Challenge& challenge) {
	int challengeIndex = this->getChallengeIndex(challenge.getTag());
	if (challengeIndex == -1) {
		return;
	}
	else if (challengeIndex == 0 && this->challengesCnt == 1) {
		delete[] this->unfulfilledChallenges;
		this->unfulfilledChallenges = new Challenge[this->challengesCapacity];
		this->challengesCnt--;
		return;
	}

	int challengesCnt = this->challengesCnt;
	Challenge* newChallenges = new Challenge[challengesCnt];

	for (size_t i = 0; i < challengesCnt - 1; i++)
	{
		if (i >= challengeIndex) {
			newChallenges[i] = this->unfulfilledChallenges[i + 1];
			continue;
		}

		newChallenges[i] = this->unfulfilledChallenges[i];
	}

	delete[] this->unfulfilledChallenges;
	this->unfulfilledChallenges = newChallenges;
	this->challengesCnt--;
}