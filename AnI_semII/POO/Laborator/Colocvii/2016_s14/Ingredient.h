#pragma once
#include<iostream>
#include<string>
using namespace std;
class Ingredient
{
protected:
	string denIng, masIng;
	double pretIng;
	static int cantIng;

public:
	Ingredient() { denIng = masIng = ""; pretIng = 0; }
	double getPret() { return pretIng; }
	friend istream& operator >> (istream&, Ingredient&);
	friend ostream& operator << (ostream&, const Ingredient&);
};
int Ingredient::cantIng = 0;
istream& operator >> (istream& in, Ingredient& I)
{
	I.cantIng++;
	cout << "Introduceti denumirea: ";
	in >> I.denIng;
	cout << "Introduceti unitatea de masura: ";
	in >> I.masIng;
	cout << "Introduceti pretul: ";
	in >> I.pretIng;
	cout << "Introduceti cantitatea: ";
	in >> I.cantIng;
	return in;
}

ostream& operator << (ostream& out, const Ingredient& I)
{
	out << "( " << I.denIng << ", " << I.pretIng << ", " << I.cantIng << ", " << I.masIng;
	return out;
}

