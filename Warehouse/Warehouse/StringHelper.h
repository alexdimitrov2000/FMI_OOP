#pragma once
#include <vector>
#include <string>
#include "SectionType.h"

using namespace std;

class StringHelper {
private:
	static int toDigit(char symbol);
public:
	static vector<string> split(const string& line, char separator = ' ');
	static string trim(const string& line);
	static int convertToInt(const string& text);
	static string sectionTypeToString(const SectionType& type);
	static string concatenate(vector<string> tokens, vector<string>::iterator from, vector<string>::iterator to);
};