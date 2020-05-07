#pragma once
#include <string>
#include <vector>
using namespace std;

class Input {
private:
	string data;
	vector<string> words;

	void copyObj(const Input& other);
	void getWord(int startIndex, int endIndex);
public:
	Input();
	Input(const string& data);
	Input(const Input& other);
	Input& operator=(const Input& other);
	
	void split();
	void clearData();

	vector<string> getTokens() const;

	void setData(const string& data);
};