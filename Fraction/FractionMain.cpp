#include <iostream>
using namespace std;
#include "Fraction.h"

int main()
{
	Fraction a(1, 3), b(4, 6);
	Fraction c = a.plus(b);
	a.print();
	b.print();
	c.print();
	return 0;
}