#include "Car.h"

void Car::copyObj(const char* model, unsigned int doors, unsigned int horsepower) {
	this->model = new char[strlen(model) + 1];
	strcpy_s(this->model, strlen(model) + 1, model);

	this->doors = doors;
	this->horsepower = horsepower;
}

void Car::copyObj(const Car& other) {
	this->copyObj(other.model, other.doors, other.horsepower);
}

void Car::erase() {
	delete[] this->model;
}

Car::Car() : Vehicle() {
	this->model = nullptr;
	this->doors = 0;
	this->horsepower = 0;
}

Car::Car(const char* color, const char* brand, unsigned int yearOfProduction, unsigned int seats, double maxSpeed,
	const char* model, unsigned int doors, unsigned int horsepower) : Vehicle(color, brand, yearOfProduction, seats, maxSpeed) {
	this->copyObj(model, doors, horsepower);
}

Car::Car(const Car& other) : Vehicle(other) {
	this->copyObj(other);
}

Car& Car::operator=(const Car& other) {
	if (this != &other) {
		Vehicle::operator=(other);
		this->erase();
		this->copyObj(other);
	}

	return *this;
}

Car::~Car() {
	this->erase();
}

char* Car::getModel() const {
	return this->model;
}

unsigned int Car::getNumOfDoors() const {
	return this->doors;
}

unsigned int Car::getHorsepower() const {
	return this->horsepower;
}

void Car::setModel(const char* model) {
	this->erase();

	this->model = new char[strlen(model) + 1];
	strcpy_s(this->model, strlen(model) + 1, model);
}

void Car::setDoors(unsigned int doors) {
	this->doors = doors;
}

void Car::setHorsepower(unsigned int horsepower) {
	this->horsepower = horsepower;
}

void Car::move() const {
	cout << "Vroom vroom" << endl;
}

ostream& operator<<(ostream& output, const Car& car) {
	output << "Car color: " << car.getColor() << endl;
	output << "Car brand: " << car.getBrand() << endl;
	output << "Car year of production: " << car.getYearOfProduction() << endl;
	output << "Car number of seats: " << car.getNumOfSeats() << endl;
	output << "Car max speed: " << car.getMaxSpeed() << endl;
	output << "Car model: " << car.model << endl;
	output << "Car number of doors: " << car.doors << endl;
	output << "Car brake horsepower: " << car.horsepower << endl;

	return output;
}