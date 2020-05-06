#include <iostream>
#include "Input.h"
#include "System.h"
using namespace std;

const int DEFAULT_INPUT_LENGTH = 200;
const char WELCOME_MESSAGE[] = "Welcome to our new 'StayHomeChallenges' application! \nYou can enter one of the following commands: 'registration', 'challenge', 'finish', 'profile_info', 'list_by'.\n";
const char USER_INPUT_MESSAGE[] = "Please, enter your command or type 'Exit' if you want to quit: ";
const char EXIT_MESSAGE[] = "You exited successfully!";

// Commands
const char REGISTRATION_COMMAND[] = "registration";
const char CHALLENGE_COMMAND[] = "challenge";
const char FINISH_COMMAND[] = "finish";
const char PROFILE_INFO_COMMAND[] = "profile_info";
const char LIST_BY_COMMAND[] = "list_by";
const char EXIT_COMMAND[] = "Exit";

// Command Messages
const char INVALID_COMMAND_MESSAGE[] = "Invalid command.";

int main()
{
	cout << WELCOME_MESSAGE << endl;
	char userInput[DEFAULT_INPUT_LENGTH];
	cout << USER_INPUT_MESSAGE;
	cin.getline(userInput, DEFAULT_INPUT_LENGTH);

	System system;

	while (strcmp(userInput, EXIT_COMMAND) != 0)
	{
		Input input(userInput);
		input.split();

		Word command = input.getCommand();
		Word* tokens = input.getTokens();
		size_t tokensCnt = input.getTokensCnt();

		if (command == REGISTRATION_COMMAND) {
			system.registerUser(tokens, tokensCnt);
		}
		else if (command == CHALLENGE_COMMAND) {
			system.challengeUser(tokens, tokensCnt);
		}
		else if (command == FINISH_COMMAND) {
			system.finishChallenge(tokens, tokensCnt);
		}
		else if (command == PROFILE_INFO_COMMAND) {
			system.printUserData(tokens[0]);
		}
		else if (command == LIST_BY_COMMAND) {
			system.printSortedChallenges(tokens[0]);
		}
		else {
			cout << INVALID_COMMAND_MESSAGE << endl;
		}

		cout << USER_INPUT_MESSAGE;
		cin.getline(userInput, DEFAULT_INPUT_LENGTH);
	}

	cout << EXIT_MESSAGE << endl;
}