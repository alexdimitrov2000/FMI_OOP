#include <cstring>
#include "Vehicle.h"

void Vehicle::copyObj(const char* color, const char* brand, unsigned int yearOfProd, unsigned int seats, double maxSpeed) {
	this->color = new char[strlen(color) + 1];
	strcpy_s(this->color, strlen(color) + 1, color);

	this->brand = new char[strlen(brand) + 1];
	strcpy_s(this->brand, strlen(brand) + 1, brand);

	this->yearOfProduction = yearOfProd;
	this->seats = seats;
	this->maxSpeed = maxSpeed;
}

void Vehicle::copyObj(const Vehicle& other) {
	this->copyObj(other.color, other.brand, other.yearOfProduction, other.seats, other.maxSpeed);
}

void Vehicle::erase() {
	delete[] this->color;
	delete[] this->brand;
}

Vehicle::Vehicle() {
	this->color = nullptr;
	this->brand = nullptr;
	this->yearOfProduction = 0;
	this->seats = 0;
	this->maxSpeed = 0.0;
}

Vehicle::Vehicle(const char* color, const char* brand, unsigned int yearOfProduction, unsigned int seats, double maxSpeed) {
	this->copyObj(color, brand, yearOfProduction, seats, maxSpeed);
}

Vehicle::Vehicle(const Vehicle& other) {
	this->copyObj(other);
}

Vehicle& Vehicle::operator=(const Vehicle& other) {
	if (this != &other) {
		this->erase();
		this->copyObj(other);
	}

	return *this;
}

Vehicle::~Vehicle() {
	this->erase();
}

char* Vehicle::getColor() const {
	return (this->color == NULL) ? nullptr : this->color;
}

char* Vehicle::getBrand() const {
	return this->brand;
}

unsigned int Vehicle::getYearOfProduction() const {
	return this->yearOfProduction;
}

unsigned int Vehicle::getNumOfSeats() const {
	return this->seats;
}

double Vehicle::getMaxSpeed() const {
	return this->maxSpeed;
}

void Vehicle::setColor(const char* color) {
	delete[] this->color;

	this->color = new char[strlen(color) + 1];
	strcpy_s(this->color, strlen(color) + 1, color);
}

void Vehicle::setBrand(const char* brand) {
	delete[] this->brand;

	this->brand = new char[strlen(brand) + 1];
	strcpy_s(this->brand, strlen(brand) + 1, brand);
}

void Vehicle::setYearOfProd(const unsigned int yearOfProd) {
	this->yearOfProduction = yearOfProd;
}

void Vehicle::setSeats(const unsigned int seats) {
	this->seats = seats;
}

void Vehicle::setMaxSpeed(const double maxSpeed) {
	this->maxSpeed = maxSpeed;
}

bool Vehicle::hasFourWheels() {
	return true;
}

void Vehicle::move() const {
	cout << "Brrrm" << endl;
}

void Vehicle::introduce() const {
	cout << "Hi! I'm a " << this->color << " " << this->brand << "." << endl;
}

ostream& operator<<(ostream& output, const Vehicle& vehicle) {
	output << "Vehicle color: " << vehicle.color << endl;
	output << "Vehicle brand: " << vehicle.brand << endl;
	output << "Vehicle year of production: " << vehicle.yearOfProduction << endl;
	output << "Vehicle number of seats: " << vehicle.seats << endl;
	output << "Vehicle max speed: " << vehicle.maxSpeed << endl;

	return output;
}