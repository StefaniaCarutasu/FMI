#pragma once
#include<iostream>
using namespace std;

class Fraction
{
	unsigned int n, m;

public:
	Fraction();
	Fraction(int, int);
	int getNumarator() const;
	int getNumitor() const;
	void setNumarator(int);
	void setNumitor(int);
	void aplificare(Fraction);
	Fraction operator = (Fraction);
	Fraction operator + (Fraction);
	Fraction operator - (Fraction);
	Fraction operator * (Fraction);
	Fraction operator / (Fraction);
	friend ostream& operator << (ostream&, Fraction&);
	friend istream& operator >> (istream&, Fraction&);
};