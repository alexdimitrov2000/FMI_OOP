#pragma once
#include "Word.h"

const short int TAG_MAX_LENGTH = 28;

enum class ChallengeStatus {
	New,
	Quite_Recently,
	Old
};

class Challenge {
private:
	float rating;
	ChallengeStatus status;
	unsigned short int sendingsCnt;
	unsigned short int finishesCnt;
	char tag[TAG_MAX_LENGTH];

	void copyObj(const char* tag, ChallengeStatus status, float rating, unsigned short int sendings, unsigned short int finishes);

public:
	Challenge();
	Challenge(const char* tag);
	Challenge(Word& tag);
	Challenge(const Challenge& other);
	Challenge& operator=(const Challenge& other);
	bool operator==(const char* tag);
	bool operator==(Word& tag);
	bool operator==(const Challenge& other);
	
	char* getTag();
	ChallengeStatus getStatus();
	float getRating() const;
	unsigned short int getNumberOfSendings() const;
	unsigned short int getNumberOfFinishes() const;

	void setTag(const char* tag);
	void setStatus(ChallengeStatus status);
	void setRating(float rating);
	void increaseSendings();
	void increaseFinishes();
};