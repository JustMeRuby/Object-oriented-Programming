#include <iostream>
using namespace std;
#include "Fraction.h"

int gcd(int a, int b)
{
    if (b == 0) return a;
    gcd(b, a % b);
}

Fraction Fraction::plus(Fraction b) const
{
    /*
    int n = numerator * b.denominator + denominator * b.numerator;
    int d = denominator * b.denominator;
    Fraction c(d, n);
    return c;
    */
    return Fraction(numerator * b.denominator + denominator * b.numerator, denominator * b.denominator);
}

void Fraction::set(int n, int d)
{
    numerator = n;
    denominator = d;
    simplify();
}

void Fraction::simplify()
{
    int u = gcd(numerator, denominator);
    numerator /= u;
    denominator /= u;
    if (denominator < 0)
    {
        numerator = -numerator, denominator = -denominator;
    }
}

void Fraction::print() const
{
    cout << numerator;
    if (numerator != 0 && denominator != 1)
    {
        cout << "/" << denominator;
    }
    cout << "\n";
}
