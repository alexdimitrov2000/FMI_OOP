#pragma once
#include <vector>
#include <string>
#include <regex>

using namespace std;

class StringHelper {
public:
	static vector<string> split(const string& line);
	static string trim(const string& line);
};

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
	return regex_replace(line, std::regex("^ +"), "");
}