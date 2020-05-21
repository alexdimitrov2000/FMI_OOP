#pragma once
#include <vector>
#include <string>

using namespace std;

class StringHelper {
private:
	static int toDigit(char symbol);
public:
	static vector<string> split(const string& line);
	static string trim(const string& line);
	static int convertToInt(const string& text);
};