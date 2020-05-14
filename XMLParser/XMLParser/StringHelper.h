#pragma once
#include <string>
#include <regex>

using namespace std;

class StringHelper {
public:
	static string trim(const string& line);
};

string StringHelper::trim(const string& line) {
	return regex_replace(line, std::regex("^ +"), "");
}