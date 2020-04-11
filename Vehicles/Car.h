#pragma once
#include "Vehicle.h"

class Car : public Vehicle {
private:
	char* model;
	unsigned int doors;
	unsigned int horsepower;

	void copyObj(const char* model, unsigned int doors, unsigned int horsepower);
	void copyObj(const Car&);
	void erase();
public:
	Car();
	Car(const char* color, const char* brand, unsigned int yearOfProduction, unsigned int seats, double maxSpeed, const char* model, unsigned int doors, unsigned int horsepower);
	Car(const Car& other);
	Car& operator=(const Car& other);
	~Car();

	char* getModel() const;
	unsigned int getNumOfDoors() const;
	unsigned int getHorsepower() const;

	void setModel(const char* model);
	void setDoors(unsigned int doors);
	void setHorsepower(unsigned int horsepower);

	void move() const override;

	friend ostream& operator<<(ostream& output, const Car& car);
};