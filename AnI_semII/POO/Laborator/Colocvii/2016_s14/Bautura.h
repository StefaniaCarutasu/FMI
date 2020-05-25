#pragma once
#include<iostream>
#include<string>
using namespace std;
class Bautura
{
	string denBaut;
	double pretBaut;
public:
	friend istream& operator >> (istream&, Bautura&);
	friend ostream& operator << (ostream&, const Bautura&);
};

istream& operator >> (istream& in, Bautura& B)
{
	in >> B.denBaut >> B.pretBaut;
}

ostream& operator << (ostream& out, const Bautura& B)
{
	out << B.denBaut << " " << B.pretBaut;
}

