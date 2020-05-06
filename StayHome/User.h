#pragma once
#include "Challenge.h"

const int EMAIL_MAX_LENGTH = 101;

class User {
private:
	char* name;
	int age;
	char email[EMAIL_MAX_LENGTH];
	unsigned int id;
	Challenge* unfulfilledChallenges;
	unsigned short int challengesCnt;
	unsigned short int challengesCapacity;

	void erase();
	void resizeChallenges();
	int getChallengeIndex(const char* tag);
public:
	User();
	User(const char* name);
	User(const char* name, int age);
	User(const char* name, const char* email);
	User(const char* name, int age, const char* email);
	User(const User& other);
	User& operator=(const User& other);
	bool operator==(const char* name);
	~User();

	char* getName() const;
	int getAge() const;
	char* getEmail();
	unsigned int getId() const;
	Challenge* getChallenges();
	unsigned short int getNumberOfUnfulfilledChallenges() const;
	bool containsChallenge(const char* tag);

	void setName(const char* name);
	void setAge(int age);
	void setEmail(const char* email);
	void setId(unsigned int id);

	bool hasAge();
	bool hasEmail();

	void addChallenge(Challenge& challenge);
	void removeChallenge(Challenge& challenge);
};