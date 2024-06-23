#pragma once

class Fraction
{
	int numerator, denominator;
public:
	Fraction(int n, int d) { set(n, d); }
	Fraction plus(Fraction b) const;
	void set(int n, int d);
	void simplify();
	void print() const;
};