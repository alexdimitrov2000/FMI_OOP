#include "Date.h"
#include "StringHelper.h"

const char DATE_PREFIX_ZERO = '0';
const char DATE_DELIMITER = '-';
const unsigned int DEFAULT_YEAR = 1900;

Date::Date() : day(0), month(0), year(0) {}

Date::Date(const string& date) {
	vector<string> tokens = StringHelper::split(date, DATE_DELIMITER);

	this->year = StringHelper::convertToInt(tokens[0]);
	this->month = StringHelper::convertToInt(tokens[1]);
	this->day = StringHelper::convertToInt(tokens[2]);
}

Date::Date(unsigned short int day, unsigned short int month, unsigned short int year) : day(day), month(month), year(year) {}

Date::Date(tm* gmtTime) : day(gmtTime->tm_mday), month(gmtTime->tm_mon + 1), year(gmtTime->tm_year + DEFAULT_YEAR) {}

Date::Date(tm& gmtTime) : day(gmtTime.tm_mday), month(gmtTime.tm_mon + 1), year(gmtTime.tm_year + DEFAULT_YEAR) {}

Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year) {}

Date& Date::operator=(const Date& other) {
	if (this != &other)
	{
		this->day = other.day;
		this->month = other.month;
		this->year = other.year;
	}

	return *this;
}

bool Date::operator==(const Date& other) {
	return this->year == other.year && this->month == other.month && this->day == other.day;
}

bool Date::operator!=(const Date& other) {
	return this->year != other.year || this->month != other.month || this->day != other.day;
}

bool Date::operator>=(const Date& other) {
	if (*this == other) { return true; }
	
	if (this->year > other.year) { return true; }
	else if (this->year == other.year) {
		if (this->month > other.month) { return true; }
		else if (this->month == other.month) {
			if (this->day > other.day) { return true; }
		}
	}

	return false;
}

bool Date::operator<=(const Date& other) {
	if (*this == other) { return true; }

	if (this->year < other.year) { return true; }
	else if (this->year == other.year) {
		if (this->month < other.month) { return true; }
		else if (this->month == other.month) {
			if (this->day < other.day) { return true; }
		}
	}

	return false;
}

unsigned short int Date::getDay() const {
	return this->day;
}

unsigned short int Date::getMonth() const {
	return this->month;
}

unsigned short int Date::getYear() const {
	return this->year;
}

void Date::setDay(unsigned short int day) {
	this->day = day;
}

void Date::setMonth(unsigned short int month) {
	this->month = month;
}

void Date::setYear(unsigned short int year) {
	this->year = year;
}

ostream& operator<<(ostream& output, const Date& date) {
	output << date.year << DATE_DELIMITER;
	if (date.month < 10)
	{
		output << DATE_PREFIX_ZERO << date.month << DATE_DELIMITER;
	}
	else {
		output << date.month << DATE_DELIMITER;
	}

	if (date.day < 10)
	{
		output << DATE_PREFIX_ZERO << date.day;
	}
	else {
		output << date.day;
	}

	return output;
}