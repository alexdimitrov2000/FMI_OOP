#pragma once
#include "User.h"
#include "Word.h"

class System {
private:
	User* users;
	Challenge* challenges;
	int usersCnt;
	int usersCapacity;
	unsigned short int challengesCnt;
	unsigned short int challengesCapacity;

	void erase();
	void copyObj(const System& other);

	bool isUserRegistered(const char* name);
	int getUserIndexIfExists(char* name, int startInde = 0);
	int getUserIndexIfExists(int id);
	void resizeUsers();
	void resizeChallenges();
	int getChallengeIndexIfExists(Word& tag);
	bool areAllRegistered(Word* users, size_t usersCnt);
	bool isTagValid(Word& tag);
	void addChallengeToUsers(Word* userNames, size_t usersCnt, Challenge& challenge);
	const char* toStringStatus(ChallengeStatus status);
	void reverseChallenges(Challenge* challenges, int challengesCnt);
	void sortByMostPopular(Challenge* challenges, int challengesCnt);
public:
	System();
	System(const System& other);
	System& operator=(const System& other);
	~System();

	void registerUser(Word* data, size_t size);

	void challengeUser(Word* data, size_t size);

	void finishChallenge(Word* data, size_t size);

	void printUserData(Word username);

	void printSortedChallenges(Word criteria);
};