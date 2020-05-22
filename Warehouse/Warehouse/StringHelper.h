#pragma once
#include <vector>
#include <string>
#include "SectionType.h"

using namespace std;

class StringHelper {
private:
	static int toDigit(char symbol);
public:
	static vector<string> split(const string& line);
	static string trim(const string& line);
	static int convertToInt(const string& text);
	static string sectionTypeToString(const SectionType& type);
};