#include <iostream>
#include "Warehouse.h"
#include "FileManager.h"
#include "StringHelper.h"

const char WELCOME_MESSAGE[] = "Welcome to our 'Warehouse' application! \nYou can enter 'help' for commands info.\n";
const char USER_INPUT_MESSAGE[] = "Please, enter your command or type 'exit' if you want to quit: ";
const char EXIT_MESSAGE[] = "Exiting the program...";

// Commands
const char OPEN_COMMAND[] = "open";
const char SAVE_COMMAND[] = "save";
const char SAVE_AS_COMMAND[] = "saveas";
const char CLOSE_COMMAND[] = "close";
const char HELP_COMMAND[] = "help";
const char EXIT_COMMAND[] = "exit";

// Command Messages
const char CLOSE_OPENED_FILE_MESSAGE[] = "There is an opened file. Please close it before you open another one.";
const char UNOPENED_FILE_MESSAGE[] = "There is no file opened. You have to open a file at first.";
const char INVALID_COMMAND_MESSAGE[] = "Invalid command.";

int main()
{
	cout << WELCOME_MESSAGE << endl;
	string userInput;
	cout << USER_INPUT_MESSAGE;
	getline(cin, userInput);

	FileManager fileManager;

	while (userInput != EXIT_COMMAND)
	{
		vector<string> tokens = StringHelper::split(userInput);
		string command = tokens[0];

		if (command == OPEN_COMMAND && fileManager.isFileOpened()) {
			cout << CLOSE_OPENED_FILE_MESSAGE << endl;
		}
		else if (command == OPEN_COMMAND) {
			string filePath = tokens[1];
			fileManager.open(filePath);

			if (!fileManager.isFileOpened())
				fileManager.isFileOpened(true);
		}
		else if (command == HELP_COMMAND) {
			fileManager.help();
		}
		else if (!fileManager.isFileOpened()) {
			cout << UNOPENED_FILE_MESSAGE << endl;
		}
		else if (command == SAVE_COMMAND) {
			fileManager.save();
		}
		else if (command == SAVE_AS_COMMAND) {
			string filePath = tokens[1];
			fileManager.saveAs(filePath);
		}
		else if (command == CLOSE_COMMAND) {
			fileManager.close();
		}
		else {
			cout << INVALID_COMMAND_MESSAGE << endl;
		}

		cout << USER_INPUT_MESSAGE;
		getline(cin, userInput);
	}

	cout << EXIT_MESSAGE << endl;
}