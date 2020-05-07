#include <iostream>
#include <vector>
#include <regex>
#include "Element.h"
#include "FileManager.h"

template <typename T>
void print(vector<T> seq) {
	int size = seq.size();
	for (size_t i = 0; i < size; i++)
	{
		cout << seq[i] << " ";
	}
	cout << endl;
}

int main() 
{
	/*vector<int> nums;
	nums.push_back(1);
	nums.push_back(3);
	nums.push_back(2);
	nums.push_back(5);
	nums.push_back(4);
	print(nums);
	nums.pop_back();
	print(nums);
	cout << nums.at(2) << endl;
	int iter = nums.back();
	cout << iter << endl;
	cout << nums.capacity() << endl;
	int* data = nums.data();
	cout << data[0] << endl;
	cout << boolalpha << nums.empty() << endl;
	cout << nums.front() << endl;
	cout << nums.size() << endl;
	nums.clear();
	cout << boolalpha << nums.empty() << endl;*/

	/*Attribute attr;

	attr.setName("src");
	attr.setValue("../images/img.png");*/

	//cout << attr.getName() << ": " << attr.getValue() << endl;

	/*Element element;
	element.setId("1_1");
	element.setTag("img");
	element.setIsTagSelfClosed(true);
	element.addAttribute(attr);
	
	Element el2("div");
	el2.setId("2");
	el2.addChildElement(element);
	el2.addAttribute(attr);
	
	Element el3("div");
	el3.setId("3");
	el3.addChildElement(el2);

	cout << el3;
	*/
	/*const string s = "             <img src=\"images/img\" alt\"img\" />          <asd></asd>";
	regex rgx("<([^>]+)>");
	smatch match;

	if (regex_search(s.begin(), s.end(), match, rgx)) {
		cout << "match: " << match[0] << '\n';
		cout << "match 1: " << match[1] << '\n';
	}*/

	// FileManager fileManager;
	// fileManager.open("test.xml");
	// 
	// cout << fileManager.getFileContent()[1] << endl;
	// cout << fileManager.getFileContent()[2] << endl;
	// 
	// fileManager.save();
	// 
	// string filePath = "D:\\Downloads\\soldProducts.xml";
	// fileManager.saveAs(filePath);
	// 
	// fileManager.help();
	// 
	// fileManager.close();


	cout << endl;
}