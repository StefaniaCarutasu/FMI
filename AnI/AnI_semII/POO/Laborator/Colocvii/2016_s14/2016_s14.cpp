#include<iostream>
#include"Ingredient.h"
#include"Pizza.h"
#include"PizzaSpec.h"
using namespace std;
int main()
{
	vector<Pizza*> p;
	vector<Ingredient*> i;
	int meniu;
	cin >> meniu;
	switch (meniu)
	{
	case 1: //meniu demo
	{
		int optiune;
		cin >> optiune;
		switch (optiune)
		{
		case 1: //insertie noua pizza
		{
			Pizza* piz = new Pizza;
			cin >> *piz;
			for (auto j : piz->getIngrediente())
				i.push_back(j);
			p.push_back(piz);
			break;
		}
		case 2: //afisare pizza
		{
			for (auto piz : p)
				cout << *piz;
			break;
		}
		default:
			break;
		}
	}
	case 2: //varianta completa
	{
		int optiune;
		cin >> optiune;
		switch (optiune)
		{
		case 1: //toate ingredientele
		{
			for (auto ing : i)
				cout << *ing;
			break;
		}
		case 2: //insertie pizza speciala
		{
			Pizza* piz = new PizzaSpec;
			cin >> *piz;
			p.push_back(piz);
			PizzaSpec* ob = dynamic_cast<PizzaSpec*> (piz);
			for (auto j : ob->getIngExtra())
				i.push_back(j);
			break;
		}
		case 3: //afisare toate pizza
		{
			for (auto piz : p)
				cout << piz << piz->getPret() << " ";
		}
		default:
			break;
		}
	}
	default:
		break;
	}

	return 0; 
}