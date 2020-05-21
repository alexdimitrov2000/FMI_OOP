#pragma once
#include <ostream>
using namespace std;

class Date {
private:
	unsigned short int day;
	unsigned short int month;
	unsigned short int year;

public:
	Date();
	Date(unsigned short int day, unsigned short int month, unsigned short int year);
	Date(tm* gmtTime);
	Date(tm& gmtTime);
	Date(const Date& other);
	Date& operator=(const Date& other);

	unsigned short int getDay() const;
	unsigned short int getMonth() const;
	unsigned short int getYear() const;

	void setDay(unsigned short int day);
	void setMonth(unsigned short int month);
	void setYear(unsigned short int year);

	friend ostream& operator<<(ostream& output, const Date& date);
};