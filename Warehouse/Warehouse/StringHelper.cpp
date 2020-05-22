#include <regex>
#include "StringHelper.h"

vector<string> StringHelper::split(const string& line) {
	int lastSpaceIndex = 0;
	int lineLength = line.size();

	vector<string> tokens;

	for (int i = 0; i < lineLength; i++)
	{
		if (line[i] == ' ') {
			tokens.push_back(line.substr(lastSpaceIndex, i - lastSpaceIndex));
			lastSpaceIndex = i + 1;
		}
	}
	tokens.push_back(line.substr(lastSpaceIndex, lineLength - lastSpaceIndex));

	return tokens;
}

string StringHelper::trim(const string& line) {
	return regex_replace(line, regex("^\\s+"), "");
}

int StringHelper::toDigit(char symbol) {
	return symbol - '0';
}

int StringHelper::convertToInt(const string& text) {
	int result = 0;

	for (size_t i = 0; i < text.size(); i++)
	{
		result = (result * 10) + toDigit(text[i]);
	}

	return result;
}

string StringHelper::sectionTypeToString(const SectionType& type) {
	switch (type)
	{
	case SectionType::Foods:
		return "Foods";
	case SectionType::Drinks:
		return "Drinks";
	case SectionType::Others:
		return "Others";
	default:
		break;
	}
}