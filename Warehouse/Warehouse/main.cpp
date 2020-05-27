#include <iostream>
#include "Warehouse.h"
#include "FileManager.h"
#include "StringHelper.h"

const char WELCOME_MESSAGE[] = "Welcome to our 'Warehouse' application! \nYou can enter 'help' for commands info.\n";
const char USER_INPUT_MESSAGE[] = "Please, enter your command or type 'exit' if you want to quit: ";
const char EXIT_MESSAGE[] = "Exiting the program...";
const char OPERATIONS_MESSAGE[] = "The following operations are supported:\n"
								  "print\n"
								  "productTypes\n"
								  "add <type> <name> <manufacturer> <unit> <expiryDate> <quantity> <comment>\n"
								  "remove <name> <quantity>\n"
								  "log <from> <to>\n"
								  "clean\n"
								  "Keep in mind that all dates are in format YYYY-MM-DD.";

// Commands
const char OPEN_COMMAND[] = "open";
const char SAVE_COMMAND[] = "save";
const char SAVE_AS_COMMAND[] = "saveas";
const char CLOSE_COMMAND[] = "close";
const char HELP_COMMAND[] = "help";
const char OPERATIONS_COMMAND[] = "operations";
const char PRODUCT_TYPES_COMMAND[] = "productTypes";
const char EXIT_COMMAND[] = "exit";
const char PRINT_COMMAND[] = "print";
const char ADD_COMMAND[] = "add";
const char REMOVE_COMMAND[] = "remove";
const char LOG_COMMAND[] = "log";
const char CLEAN_COMMAND[] = "clean";

// Command Messages
const char CLOSE_OPENED_FILE_MESSAGE[] = "There is an opened file. Please close it before you open another one.";
const char UNOPENED_FILE_MESSAGE[] = "There is no file opened. You have to open a file at first.";
const char SUPPORTED_PRODUCT_TYPES_MESSAGE[] = "Supported product types: Foods/Drinks/Others";
const char INVALID_COMMAND_MESSAGE[] = "Invalid command.";

int main()
{
	cout << WELCOME_MESSAGE << endl;
	string userInput;
	cout << USER_INPUT_MESSAGE;
	getline(cin, userInput);

	FileManager fileManager;
	Warehouse warehouse;

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

			warehouse.build();

			warehouse.addFileProducts(fileManager.getFileContent());
		}
		else if (command == HELP_COMMAND) {
			fileManager.help();
		}
		else if (!fileManager.isFileOpened()) {
			cout << UNOPENED_FILE_MESSAGE << endl;
		}
		else if (command == SAVE_COMMAND) {
			fileManager.setProducts(warehouse.getProducts());
			fileManager.save();
		}
		else if (command == SAVE_AS_COMMAND) {
			fileManager.setProducts(warehouse.getProducts());
			string filePath = tokens[1];
			fileManager.saveAs(filePath);
		}
		else if (command == CLOSE_COMMAND) {
			fileManager.close();

			warehouse.destroy();
		}
		else if (command == OPERATIONS_COMMAND) {
			cout << OPERATIONS_MESSAGE << endl;
		}
		else if (command == PRODUCT_TYPES_COMMAND) {
			cout << SUPPORTED_PRODUCT_TYPES_MESSAGE << endl;
		}
		else if (command == PRINT_COMMAND) {
			warehouse.printProducts();
		}
		else if (command == ADD_COMMAND) {
			tokens.erase(tokens.begin()); // remove the 'add' command string from the vector
			Product* product = warehouse.addProduct(tokens);

			fileManager.logsAddProduct(product);
		}
		else if (command == REMOVE_COMMAND) {
			string name = tokens[1];
			string quantityStr = tokens[2];

			warehouse.remove(name, quantityStr);

			fileManager.logsRemoveProduct(name, quantityStr);
		}
		else if (command == LOG_COMMAND) {
			string from = tokens[1];
			string to = tokens[2];

			fileManager.showLogInInterval(from, to);
		}
		else if (command == CLEAN_COMMAND) {
			warehouse.clean();
			fileManager.logsCleanWarehouse();
		}
		else {
			cout << INVALID_COMMAND_MESSAGE << endl;
		}

		cout << USER_INPUT_MESSAGE;
		getline(cin, userInput);
	}

	cout << EXIT_MESSAGE << endl;
}