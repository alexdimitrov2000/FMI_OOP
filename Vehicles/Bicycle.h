#pragma once
#include "Vehicle.h"

class Bicycle : public Vehicle {
private:
	unsigned int gears;
	bool hasReflector;
	bool hasBell;

	void copyObj(unsigned int, bool, bool);

public:
	Bicycle();
	Bicycle(const char* color, const char* brand, unsigned int yearOfProduction, unsigned int seats, double maxSpeed, unsigned int gears, bool hasReflector, bool hasBell);
	Bicycle(const Bicycle& other);
	Bicycle& operator=(const Bicycle& other);
	
	unsigned int getGears() const;
	bool getHasReflector() const;
	bool getHasBell() const;

	void setGears(const unsigned int gears);
	void setHasReflector(const bool hasReflector);
	void setHasBell(const bool hasBell);

	bool hasFourWheels() override;
	void move() const override;
	void introduce() const override;

	friend ostream& operator<<(ostream& output, const Bicycle& bicycle);
};