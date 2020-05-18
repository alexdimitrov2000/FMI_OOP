#include <iostream>
#include <vector>
#include "FileManager.h"
#include "XmlParser.h"

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
const char OPERATIONS_COMMAND[] = "operations";
const char PRINT_COMMAND[] = "print";
const char SELECT_COMMAND[] = "select";
const char SET_COMMAND[] = "set";
const char CHILDREN_COMMAND[] = "children";
const char CHILD_COMMAND[] = "child";
const char TEXT_COMMAND[] = "text";
const char DELETE_COMMAND[] = "delete";
const char NEWCHILD_COMMAND[] = "newchild";
const char XPATH_COMMAND[] = "xpath";

// Command Messages
const char UNOPENED_FILE_MESSAGE[] = "There is no file opened. You have to open a file at first.";
const char INVALID_COMMAND_MESSAGE[] = "Invalid command.";
//const char OPERATIONS_INFO_MESSAGE[] = "print -> outputs the information read from the file\n"
//									   "select <id> <key> -> outputs the value of the attribute with <key> of the element with <id>\n"
//									   "set <id> <key> <value> -> sets <value> to the attribute with <key> of the element with <id>\n"
//									   "children <id> -> gets list with attributes of the element with <id> children\n";

int main()
{
	cout << WELCOME_MESSAGE << endl;
	string userInput;
	cout << USER_INPUT_MESSAGE;
	getline(cin, userInput);

	FileManager fileManager;
	XmlParser parser;

	while (userInput != EXIT_COMMAND)
	{
		vector<string> tokens = StringHelper::split(userInput);
		string command = tokens[0];

		if (command == OPEN_COMMAND) {
			string filePath = tokens[1];
			fileManager.open(filePath);

			parser.parse(fileManager.getFileContent());

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
		else if (command == OPERATIONS_COMMAND) {
			
		}
		else if (command == PRINT_COMMAND) {
			parser.print();
		}
		else if (command == SELECT_COMMAND) {
			string id = tokens[1];
			string key = tokens[2];

			parser.selectElementAttr(id, key);
		}
		else if (command == SET_COMMAND) {
			string id = tokens[1];
			string key = tokens[2];
			string value = tokens[3];

			parser.setElementAttrValue(id, key, value);
		}
		else if (command == CHILDREN_COMMAND) {

		}
		else if (command == CHILD_COMMAND) {
			string id = tokens[1];
			string childIndex = tokens[2];

			Element* nthChild = parser.getNthChild(id, childIndex);

			if (nthChild != nullptr) {
				cout << (*nthChild) << endl;
			}
		}
		else if (command == TEXT_COMMAND) {
			string id = tokens[1];

			string elementContent = parser.getContent(id);

			cout << elementContent << endl;
		}
		else if (command == DELETE_COMMAND) {

		}
		else if (command == NEWCHILD_COMMAND) {

		}
		else if (command == XPATH_COMMAND) {

		}
		else {
			cout << INVALID_COMMAND_MESSAGE << endl;
		}

		cout << USER_INPUT_MESSAGE;
		getline(cin, userInput);
	}

	cout << EXIT_MESSAGE << endl;
}