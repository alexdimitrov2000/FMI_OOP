#pragma once
#include <iostream>
using namespace std;

class Vehicle {
private:
	char* color;
	char* brand;
	unsigned int yearOfProduction;
	unsigned int seats;
	double maxSpeed;

	void copyObj(const char*, const char*, unsigned int, unsigned int, double);
	void copyObj(const Vehicle&);
	void erase();

public:
	Vehicle();
	Vehicle(const char* color, const char* brand, unsigned int yearOfProduction, unsigned int seats, double maxSpeed);
	Vehicle(const Vehicle& other);
	Vehicle& operator=(const Vehicle& other);
	~Vehicle();

	char* getColor() const;
	char* getBrand() const;
	unsigned int getYearOfProduction() const;
	unsigned int getNumOfSeats() const;
	double getMaxSpeed() const;

	void setColor(const char* color);
	void setBrand(const char* color);
	void setYearOfProd(const unsigned int yearOfProd);
	void setSeats(const unsigned int seats);
	void setMaxSpeed(const double maxSpeed);

	virtual bool hasFourWheels();
	virtual void move() const;
	virtual void introduce() const;

	friend ostream& operator<<(ostream& output, const Vehicle& vehicle);
};