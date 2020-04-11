#include "Bicycle.h"
#include "Car.h"

int main()
{
	Vehicle v1;
	Vehicle v2("Blue", "Range Rover", 2019, 5, 240);
	Vehicle v3(v2);
	Vehicle v4 = v3;

	Bicycle b1;
	Bicycle b2("Red", "Cross", 2020, 1, 60, 24, true, false);
	Bicycle b3(b2);
	Bicycle b4 = b3;

	Car c1;
	Car c2("Black", "Toyota", 2015, 5, 180, "Auris", 4, 125);
	Car c3(c2);
	Car c4 = c3;

	cout << v2 << endl;
	cout << v3 << endl;
	cout << v4 << endl;

	cout << b2 << endl;
	cout << b3 << endl;
	cout << b4 << endl;

	cout << c2 << endl;
	cout << c3 << endl;
	cout << c4 << endl;

	v2.move();
	b2.move();
	c2.move();

	cout << v2.hasFourWheels() << endl;
	cout << b2.hasFourWheels() << endl;
	cout << c2.hasFourWheels() << endl;

	v3.introduce();
	b3.introduce();
	c3.introduce();

	cout << endl;
}