#include <iostream>
#include "Product.h"
using namespace std;

int main() 
{
	Product prod;
	prod.setName("Bread");
	Product prod2(prod);
	Product prod3 = prod2;

	cout << endl;
}