#pragma once
#include <vector>
#include <string>
#include <regex>

using namespace std;

class StringHelper {
private:
	static string getWord(int startIndex, int endIndex, const string& line);

public:
	static vector<string> split(const string& line);
	static string trim(const string& line);
};

string StringHelper::getWord(int startIndex, int endIndex, const string& line) {
	string word;

	for (int i = startIndex; i < endIndex; i++)
	{
		word += line[i];
	}

	return word;
}

vector<string> StringHelper::split(const string& line) {
	int lastSpaceIndex = 0;
	int lineLength = line.size();

	vector<string> tokens;

	for (int i = 0; i < lineLength; i++)
	{
		if (line[i] == ' ') {
			tokens.push_back(getWord(lastSpaceIndex, i, line));
			lastSpaceIndex = i + 1;
		}
	}
	tokens.push_back(getWord(lastSpaceIndex, lineLength, line));	

	return tokens;
}

string StringHelper::trim(const string& line) {
	regex rgx("<([^>]+)>");
	smatch match;
	if (regex_search(line, match, rgx)) {
		return match[1];
	}

	return line;
}