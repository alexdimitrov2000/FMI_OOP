#include <regex>
#include "StringHelper.h"

const string FOODS_TYPE = "Foods";
const string DRINKS_TYPE = "Drinks";
const string OTHERS_TYPE = "Others";
const string SPACE_DELIMITER = " ";

vector<string> StringHelper::split(const string& line, char separator) {
	int lastSpaceIndex = 0;
	int lineLength = line.size();

	vector<string> tokens;

	for (int i = 0; i < lineLength; i++)
	{
		if (line[i] == separator) {
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
		return FOODS_TYPE;
	case SectionType::Drinks:
		return DRINKS_TYPE;
	case SectionType::Others:
		return OTHERS_TYPE;
	default:
		break;
	}
}

string StringHelper::concatenate(vector<string> tokens, vector<string>::iterator from, vector<string>::iterator to) {
	string result;

	for (vector<string>::iterator i = from; i != to; i++) {
		result += (*i) + SPACE_DELIMITER;
	}
	result.pop_back();

	return result;
}