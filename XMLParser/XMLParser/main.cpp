#include <iostream>
#include <vector>
#include <regex>
#include "Element.h"
#include "FileManager.h"
#include "Input.h"

const char WELCOME_MESSAGE[] = "Welcome to our 'XML Parser' application! \nYou can enter 'help' for commands info.\n";
const char USER_INPUT_MESSAGE[] = "Please, enter your command or type 'exit' if you want to quit: ";
const char EXIT_MESSAGE[] = "Exiting the program...";

// Commands
const char OPEN_COMMAND[] = "open";
const char SAVE_COMMAND[] = "save";
const char SAVE_AS_COMMAND[] = "saveAs";
const char CLOSE_COMMAND[] = "close";
const char HELP_COMMAND[] = "help";
const char EXIT_COMMAND[] = "exit";

// Command Messages
const char INVALID_COMMAND_MESSAGE[] = "Invalid command.";

int main()
{
	cout << WELCOME_MESSAGE << endl;
	string userInput;
	cout << USER_INPUT_MESSAGE;
	getline(cin, userInput);
	Input input;

	while (userInput != EXIT_COMMAND)
	{
		input.setData(userInput);
		input.split();

		vector<string> tokens = input.getTokens();
		string command = tokens[0];
		size_t tokensCnt = tokens.size();

		if (command == OPEN_COMMAND) {
			cout << "open" << endl;
		}
		else if (command == SAVE_COMMAND) {
			cout << "save" << endl;
		}
		else if (command == SAVE_AS_COMMAND) {
			cout << "save as" << endl;
		}
		else if (command == CLOSE_COMMAND) {
			cout << "close" << endl;
		}
		else if (command == HELP_COMMAND) {
			cout << "help" << endl;
		}
		else {
			cout << INVALID_COMMAND_MESSAGE << endl;
		}

		cout << USER_INPUT_MESSAGE;
		input.clearData();
		getline(cin, userInput);
	}

	cout << EXIT_MESSAGE << endl;
}