#include "Fraction.h"
#include<iostream>
#include<math.h>

Fraction::Fraction() : n(0), m(0) {}
Fraction::Fraction(int numarator, int numitor) : n(numarator), m(numitor) {}
int Fraction::getNumarator() const
{
	return this->n;
}
int Fraction::getNumitor() const
{
	return this->m;
}
void Fraction::setNumarator(int x)
{
	this->n = x;
}
void Fraction::setNumitor(int x)
{
	this->m = x;
}
ostream& operator << (ostream& out, Fraction& F)
{
	out << F.getNumarator() << '/' << F.getNumitor();
	return out;

}
istream& operator >> (istream& in, Fraction& F)
{
	int n, m;
	in >> n >> m;
	F.setNumarator(n); F.setNumitor(m);
	return in;
}

Fraction Fraction::operator = (Fraction f)
{
	this->n = f.n;
	this->m = f.m;
	return *this;
}

Fraction Fraction::operator + (Fraction f)
{
	int x = this->n * f.m + this->m * f.n;
	int y = this->m * f.m;
	int cmmdc, d;
	if (x < y) d = abs(x);
	else d = abs(y);
	for (int i = 2; i <= d / 2; i++)
		if (x % d == 0 && y % d == 0)
			cmmdc = d;
	this->n = x / d;
	this->m = y / d;
	return *this;
}

Fraction Fraction::operator * (Fraction f)
{
	int x = this->n * f.n;
	int y = this->m * f.m;
	int cmmdc, d;
	if (x < y) d = abs(x);
	else d = abs(y);
	for (int i = 2; i <= d / 2; i++)
		if (x % d == 0 && y % d == 0)
			cmmdc = d;
	this->n = x / d;
	this->m = y / d;
	return *this;
}

Fraction Fraction::operator - (Fraction f)
{
	int x = this->n * f.m - this->m * f.n;
	int y = this->m * f.m;
	int cmmdc, d;
	if (x < y) d = abs(x);
	else d = abs(y);
	for (int i = 2; i <= d / 2; i++)
		if (x % d == 0 && y % d == 0)
			cmmdc = d;
	this->n = x / d;
	this->m = y / d;
	return *this;
}

Fraction Fraction::operator / (Fraction f)
{
	int x = this->n * f.m;
	int y = this->m * f.n;
	int cmmdc, d;
	if (x < y) d = abs(x);
	else d = abs(y);
	for (int i = 2; i <= d / 2; i++)
		if (x % d == 0 && y % d == 0)
			cmmdc = d;
	this->n = x / d;
	this->m = y / d;
	return *this;
}

void Fraction::aplificare(Fraction f)
{
	int x = this->n * f.n;
	int y = this->m;
	int cmmdc, d;
	if (x < y) d = abs(x);
	else d = abs(y);
	for (int i = 2; i <= d / 2; i++)
		if (x % d == 0 && y % d == 0)
			cmmdc = d;
	this->n = x / d;
	this->m = y / d;
}