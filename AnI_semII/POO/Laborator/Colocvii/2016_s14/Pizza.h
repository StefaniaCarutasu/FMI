#pragma once
#include<iostream>
#include<string>
#include<vector>
#include"Ingredient.h"
using namespace std;
class Pizza
{
protected:
	static int codPizza;
	string denPizza;
	vector<Ingredient*> ingPizza;
	int nrIngPizza;
	double pretPizza;
	bool vegPizza;
	virtual void readExtra(istream& in) {}
	virtual void displayExtra(ostream& out) const {}
public:
	Pizza()=default;
	vector<Ingredient*> getIngrediente() { return ingPizza; }
	double getPret() { return pretPizza; }
	friend istream& operator >> (istream&, Pizza&);
	friend ostream& operator << (ostream&, const Pizza&);
};

int Pizza::codPizza = 0;
istream& operator >> (istream& in, Pizza& P)
{
	P.codPizza++;
	cout << "Introduceti denumirea: ";
	in >> P.denPizza;
	cout << "Introduceti nr de ingrediente: ";
	in >> P.nrIngPizza;
	cout << "Introduceti cele " << P.nrIngPizza << " ingredinete: ";
	for (int i = 0; i < P.nrIngPizza; i++)
	{
		Ingredient* ing = new Ingredient;
		cin >> *ing;
		P.ingPizza.push_back(ing);
		P.pretPizza += ing->getPret();
	}
	P.pretPizza += P.pretPizza / 2;
	cout << "Este vegetariana? (true/false): ";
	in >> P.vegPizza;
	P.readExtra(in);
	return in;
}

ostream& operator << (ostream& out, const Pizza& P)
{
	out << "Cod: " << P.codPizza;
	out << "Denumire: " << P.denPizza;
	out << "Nr ing: " << P.nrIngPizza;
	for (auto i : P.ingPizza)
	{
		out << "Igredient: " << *i << " ";
	}
	P.displayExtra(out);
	out << '\n';
	return out;
}

