#pragma once
#include "Pizza.h"
#include"Ingredient.h"
class PizzaSpec :
	public Pizza
{
protected:
	int nrIngPizza;
	vector<Ingredient*> ingPizza;
protected:
	void readExtra(istream&);
	void displayExtra(ostream&) const;
public:
	vector<Ingredient*> getIngExtra() { return ingPizza; }
};

void PizzaSpec::readExtra(istream& in)
{
	cout << "Nr ing suplimentare: ";
	in >> PizzaSpec::nrIngPizza;
	for (int i = 0; i < PizzaSpec::nrIngPizza; i++)
	{
		cout << "Introduceti ingredient: ";
		Ingredient* ing = new Ingredient;
		cin >> *ing;
		PizzaSpec::ingPizza.push_back(ing);
		Pizza::pretPizza += ing->getPret();
	}
}

void PizzaSpec::displayExtra(ostream& out) const
{
	out << "\nIngrediente suplimentare: ";
	for (auto i : PizzaSpec::ingPizza)
		out << i << " ";
	out << "\nNr ing suplimentare: " << PizzaSpec::nrIngPizza;

}

