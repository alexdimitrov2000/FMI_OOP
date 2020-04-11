#include "Bicycle.h"

void Bicycle::copyObj(unsigned int gears, bool hasReflector, bool hasBell) {
	this->gears = gears;
	this->hasReflector = hasReflector;
	this->hasBell = hasBell;
}

Bicycle::Bicycle() : Vehicle() {
	this->gears = 0;
	this->hasReflector = false;
	this->hasBell = false;
}

Bicycle::Bicycle(const char* color, const char* brand, unsigned int yearOfProduction, unsigned int seats, double maxSpeed,
	unsigned int gears, bool hasReflector, bool hasBell) : Vehicle(color, brand, yearOfProduction, seats, maxSpeed) {
	this->copyObj(gears, hasReflector, hasBell);
}

Bicycle::Bicycle(const Bicycle& other) : Vehicle(other) {
	this->copyObj(other.gears, other.hasReflector, other.hasBell);
}

Bicycle& Bicycle::operator=(const Bicycle& other) {
	if (this != &other) {
		Vehicle::operator=(other);

		this->copyObj(other.gears, other.hasReflector, other.hasBell);
	}

	return *this;
}

unsigned int Bicycle::getGears() const {
	return this->gears;
}

bool Bicycle::getHasReflector() const {
	return this->hasReflector;
}

bool Bicycle::getHasBell() const {
	return this->hasBell;
}

void Bicycle::setGears(unsigned int gears) {
	this->gears = gears;
}

void Bicycle::setHasReflector(bool hasReflector) {
	this->hasReflector = hasReflector;
}

void Bicycle::setHasBell(bool hasBell) {
	this->hasBell = hasBell;
}

bool Bicycle::hasFourWheels() {
	return false;
}

void Bicycle::move() const {
	cout << "a nqkoi kara koolelo" << endl;
}

void Bicycle::introduce() const {
	Vehicle::introduce();
	cout << "I have " << this->gears << " gears and can speed up to " << this->getMaxSpeed() << " km/h." << endl;
}

ostream& operator<<(ostream& output, const Bicycle& bicycle) {
	output << "Bicycle color: " << bicycle.getColor() << endl;
	output << "Bicycle brand: " << bicycle.getBrand() << endl;
	output << "Bicycle year of production: " << bicycle.getYearOfProduction() << endl;
	output << "Bicycle number of seats: " << bicycle.getNumOfSeats() << endl;
	output << "Bicycle max speed: " << bicycle.getMaxSpeed() << endl;
	output << "Bicycle number of gears: " << bicycle.gears << endl;
	output << "Bicycle has reflector: " << boolalpha << bicycle.hasReflector << endl;
	output << "Bicycle has bell: " << boolalpha << bicycle.hasBell << endl;

	return output;
}