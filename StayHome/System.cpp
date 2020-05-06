#include <iostream>
#include <cstring>
#include "System.h"
using namespace std;

// Command messages
const char REGISTRATION_EMAIL_SUCCESS_MESSAGE[] = "Registration Successful. Please check your email.";
const char REGISTRATION_SUCCESS_MESSAGE[] = "Registration Successful.";
const char REGISTRATION_FAIL_MESSAGE[] = "Registration Fail. You are too old for this App.";
const char CHALLENGE_SUCCESS_MESSAGE[] = " successfully challenged!";
const char CHALLENGE_INVALID_TAG_FAIL_MESSAGE[] = "Sorry! Invalid tag of the challenge.";
const char CHALLENGE_REGISTERED_USERS_FAIL_MESSAGE[] = "Sorry, some of the users may not be registered!";
const char FINISH_CHALLENGE_SUCCESS_MESSAGE[] = "Well done! May the challenge be with you!";
const char FINISH_CHALLENGE_INVALID_ID_FAIL_MESSAGE[] = "The given id isn't valid. The user with this id do not exist.";
const char FINISH_CHALLENGE_INVALID_RATING_FAIL_MESSAGE[] = "Sorry. Invalid rating! The challenge is not completed, yet.";
const char FINISH_NOT_PARTICIPANT_FAIL_MESSAGE[] = "Sorry. User does not participate in this challenge.";
const char SEARCHING_MESSAGE[] = "Searching for users...";
const char PROFILE_INFO_FAIL_MESSAGE[] = "Nothing come out! User with this name do not exist!";
const char NO_CHALLENGES_FAIL_MESSAGE[] = "Sorry, there are no challenges, yet.";

const char DELIMITER[] = "-------------------------";

// Method for releasing the memory, allocated for users and challenges
void System::erase() {
	delete[] this->users;
	delete[] this->challenges;
}

// Method for copying data from another System object
void System::copyObj(const System& other) {
	this->usersCnt = other.usersCnt;
	this->usersCapacity = other.usersCapacity;
	this->challengesCnt = other.challengesCnt;
	this->challengesCapacity = other.challengesCapacity;
	this->users = other.users;
	this->challenges = other.challenges;
}

System::System() {
	this->users = nullptr;
	this->challenges = nullptr;
	this->usersCnt = 0;
	this->usersCapacity = 0;
	this->challengesCnt = 0;
	this->challengesCapacity = 0;
}

System::System(const System& other) {
	this->copyObj(other);
}

System& System::operator=(const System& other) {
	if (this != &other) {
		this->erase();
		this->copyObj(other);
	}

	return *this;
}

System::~System() {
	this->erase();
}

// Function that checks if a symbol is digit
bool isDigit(char symbol) {
	return symbol >= '0' && symbol <= '9';
}

// Function that checks if all of the symbols in a Word are digits and returns true if the 'text' is a number
bool isNumber(Word text) {
	char* characters = text.getCharacters();
	for (size_t i = 0; characters[i] != '\0'; i++)
	{
		if (!isDigit(characters[i])) {
			return false;
		}
	}

	return true;
}

// Function that converts a digit symbol into an integer digit
int toDigit(char symbol) {
	return symbol - '0';
}

// Function that converts a number string into an integer
int convertToInt(Word text) {
	int result = 0;
	char* characters = text.getCharacters();

	for (size_t i = 0; characters[i] != '\0'; i++)
	{
		result = (result * 10) + toDigit(characters[i]);
	}

	return result;
}

// Method for resizing the collection of users
void System::resizeUsers() {
	if (this->usersCapacity <= 0) {
		this->usersCapacity = 1;
		this->users = new User[this->usersCapacity];
		return;
	}

	this->usersCapacity *= 2;
	User* newUserCollection = new User[this->usersCapacity];

	for (int i = 0; i < this->usersCnt; i++)
	{
		newUserCollection[i] = this->users[i];
	}

	delete[] this->users;
	this->users = newUserCollection;
}

// Method for resizing the collection of challenges
void System::resizeChallenges() {
	if (this->challengesCapacity <= 0) {
		this->challengesCapacity = 1;
		this->challenges = new Challenge[this->challengesCapacity];
		return;
	}

	this->challengesCapacity *= 2;
	if (this->challengesCapacity > 65535) {
		this->challengesCapacity = 65535;
	}

	Challenge* newChallengeCollection = new Challenge[this->challengesCapacity];

	for (size_t i = 0; i < this->challengesCnt; i++)
	{
		newChallengeCollection[i] = this->challenges[i];
	}

	delete[] this->challenges;
	this->challenges = newChallengeCollection;
}

// Method that checks if an User with the passed name parameter is registered in the System
bool System::isUserRegistered(const char* name) {
	for (int i = 0; i < this->usersCnt; i++)
	{
		if (this->users[i] == name) {
			return true;
		}
	}

	return false;
}

// Method that returns the index in the this->users collection of the user with 'name'
// A startIndex param is passed so the it will be able to return indexes of all the users with that name, not only the first one
int System::getUserIndexIfExists(char* name, int startIndex) {
	for (int i = startIndex; i < this->usersCnt; i++)
	{
		if (this->users[i] == name) {
			return i;
		}
	}

	return -1;
}

// Method that returns the index in the this->users collection of the user with ID = passed id param
int System::getUserIndexIfExists(int id) {
	for (int i = 0; i < this->usersCnt; i++)
	{
		if (this->users[i].getId() == id) {
			return i;
		}
	}

	return -1;
}

// Method that returns the index in the this->challenges collection of the challenge with tag, equal to passed tagWord param
int System::getChallengeIndexIfExists(Word& tagWord) {
	char* tag = tagWord.getCharacters();

	for (size_t i = 0; i < this->challengesCnt; i++)
	{
		if (this->challenges[i] == tag) {
			return i;
		}
	}

	return -1;
}

// Method that checks if all of the passed users are registered in the system
bool System::areAllRegistered(Word* users, size_t usersCnt) {
	bool areAllRegistered = true;
	for (size_t i = 0; i < usersCnt; i++)
	{
		if (!isUserRegistered(users[i].getCharacters())) {
			areAllRegistered = false;
			break;
		}
	}

	return areAllRegistered;
}

// A method that checks if a tag is valid
bool System::isTagValid(Word& tag) {
	return tag.getCharacters()[0] == '#' && tag.getLength() <= 31;
}

// Method that adds the passed challenge param to their unfulfilledChallenges collection
void System::addChallengeToUsers(Word* userNames, size_t usersCnt, Challenge& challenge) {
	for (size_t i = 0; i < usersCnt; i++)
	{
		char* currentUserName = userNames[i].getCharacters();
		int userIndex = this->getUserIndexIfExists(currentUserName);
		this->users[userIndex].addChallenge(challenge);
	}
}

// Method that converts a passed status from enum to string
const char* System::toStringStatus(ChallengeStatus status) {
	if (status == ChallengeStatus::New) {
		return "new";
	}
	else if (status == ChallengeStatus::Old) {
		return "old";
	}

	return "quite recently";
}

// Method that reverses all of the passed challenges
void System::reverseChallenges(Challenge* challenges, int challengesCnt) {
	for (int i = 0; i < challengesCnt / 2; i++)
	{
		swap(challenges[i], challenges[challengesCnt - i - 1]);
	}
}

// Method that sorts the passed challenges by number of sendings
void System::sortByMostPopular(Challenge* challenges, int numberOfChallenges) {
	for (int i = 0; i < numberOfChallenges - 1; ++i) {
		for (int j = 0; j < numberOfChallenges - i - 1; ++j) {
			if (challenges[j].getNumberOfSendings() < challenges[j + 1].getNumberOfSendings()) {
				swap(challenges[j], challenges[j + 1]);
			}
		}
	}
}

// Method that executes the reigstration command
void System::registerUser(Word* data, size_t size) {
	const int MAX_EMAIL_LENGTH = 101;
	char* name = data[0].getCharacters();
	User user(name);

	for (size_t i = 1; i < size; i++)
	{
		if (data[i] != "") {
			if (isNumber(data[i])) {
				int age = convertToInt(data[i]);
				if (age > 90) {
					cout << REGISTRATION_FAIL_MESSAGE << endl;
					return;
				}
				user.setAge(age);
			}
			else
			{
				user.setEmail(data[i].getCharacters());
			}
		}
	}

	user.setId(this->usersCnt + 1);

	if (this->usersCnt >= this->usersCapacity) {
		this->resizeUsers();
	}

	this->users[this->usersCnt] = user;
	this->usersCnt++;

	if (user.hasEmail()) {
		cout << REGISTRATION_EMAIL_SUCCESS_MESSAGE << endl;
	}
	else {
		cout << REGISTRATION_SUCCESS_MESSAGE << endl;
	}
}

// Method that executes the challenge command
void System::challengeUser(Word* data, size_t size) {
	Word challenger = data[0];
	Word tag = data[1];
	Word* challengedUsers = data + 2;

	if (!(areAllRegistered(challengedUsers, size - 2) && isUserRegistered(challenger.getCharacters()))) {
		cout << CHALLENGE_REGISTERED_USERS_FAIL_MESSAGE << endl;
		return;
	}
	if (!isTagValid(tag)) {
		cout << CHALLENGE_INVALID_TAG_FAIL_MESSAGE << endl;
		return;
	}

	int challengeIndex = getChallengeIndexIfExists(tag);

	if (challengeIndex != -1) {
		Challenge& challenge = this->challenges[challengeIndex];

		challenge.increaseSendings();

		unsigned short int sendingsCnt = challenge.getNumberOfSendings();
		ChallengeStatus challengeStatus = challenge.getStatus();

		if (sendingsCnt >= 2 && sendingsCnt <= 10 && challengeStatus == ChallengeStatus::New) {
			challenge.setStatus(ChallengeStatus::Quite_Recently);
		}
		else if (sendingsCnt >= 11 && challengeStatus == ChallengeStatus::Quite_Recently) {
			challenge.setStatus(ChallengeStatus::Old);
		}

		this->addChallengeToUsers(challengedUsers, size - 2, challenge);

		cout << challenger.getCharacters() << CHALLENGE_SUCCESS_MESSAGE << endl;

		return;
	}

	if (this->challengesCnt >= this->challengesCapacity) {
		this->resizeChallenges();
	}

	Challenge challenge(tag);
	challenge.increaseSendings();
	this->challenges[this->challengesCnt] = challenge;
	this->challengesCnt++;

	// Adding the challenge to the users
	this->addChallengeToUsers(challengedUsers, size - 2, challenge);

	cout << challenger.getCharacters() << CHALLENGE_SUCCESS_MESSAGE << endl;
}

// Method that executes the finish command
void System::finishChallenge(Word* data, size_t size) {
	Word challengeTag = data[0];
	int userId = convertToInt(data[1]);
	float userRating;

	cout << "Rate the challenge: ";
	cin >> userRating;
	cin.ignore();

	if (userRating < -5 || userRating > 10) {
		cout << FINISH_CHALLENGE_INVALID_RATING_FAIL_MESSAGE << endl;
		return;
	}

	int userIndex = this->getUserIndexIfExists(userId);

	if (userIndex == -1) {
		cout << FINISH_CHALLENGE_INVALID_ID_FAIL_MESSAGE << endl;
		return;
	}

	int challengeIndex = this->getChallengeIndexIfExists(challengeTag);

	User& user = this->users[userIndex];
	Challenge& challenge = this->challenges[challengeIndex];

	if (!user.containsChallenge(challenge.getTag())) {
		cout << FINISH_NOT_PARTICIPANT_FAIL_MESSAGE << endl;
		return;
	}

	user.removeChallenge(challenge);

	float currentChallengeRating = challenge.getRating();
	challenge.increaseFinishes();
	int challengeFinishes = challenge.getNumberOfFinishes();
	challenge.setRating((currentChallengeRating + userRating) / challengeFinishes);

	cout << FINISH_CHALLENGE_SUCCESS_MESSAGE << endl;
}

// Method that executes the profile_info command
void System::printUserData(Word name) {
	cout << SEARCHING_MESSAGE << endl;

	int userIndex = this->getUserIndexIfExists(name.getCharacters());

	if (userIndex == -1 || !isUserRegistered(name.getCharacters())) {
		cout << PROFILE_INFO_FAIL_MESSAGE << endl;
		return;
	}

	while (userIndex != -1)
	{
		User user = this->users[userIndex];

		cout << DELIMITER << endl;
		cout << "Name: " << user.getName() << endl;
		if (user.hasAge()) {
			cout << "Age: " << user.getAge() << endl;
		}
		else {
			cout << "Age: " << "Unknown" << endl;
		}
		const char* email = user.hasEmail() ? user.getEmail() : "Unknown";
		cout << "Email: " << email << endl;
		cout << "ID: " << user.getId() << endl;

		userIndex = this->getUserIndexIfExists(name.getCharacters(), userIndex + 1);
	}
}

// Method that executes the list_by command
void System::printSortedChallenges(Word criteria) {
	if (this->challengesCnt == 0) {
		cout << NO_CHALLENGES_FAIL_MESSAGE << endl;
		return;
	}

	int challengesCnt = this->challengesCnt;
	Challenge* newChallengeCollection = new Challenge[challengesCnt];
	for (size_t i = 0; i < challengesCnt; i++)
	{
		newChallengeCollection[i] = this->challenges[i];
	}

	if (criteria == "newest") {
		this->reverseChallenges(newChallengeCollection, challengesCnt);
	}
	else if (criteria == "most_popular") {
		this->sortByMostPopular(newChallengeCollection, challengesCnt);
	}

	for (size_t i = 0; i < challengesCnt; i++)
	{
		cout << DELIMITER << endl;
		cout << "Tag: " << newChallengeCollection[i].getTag() << endl;
		cout << "Rating: " << newChallengeCollection[i].getRating() << endl;
		cout << "Status: " << toStringStatus(challenges[i].getStatus()) << endl;
		cout << "Total: " << newChallengeCollection[i].getNumberOfSendings() << endl;
		cout << "Done: " << newChallengeCollection[i].getNumberOfFinishes() << endl;
	}

	delete[] newChallengeCollection;
}