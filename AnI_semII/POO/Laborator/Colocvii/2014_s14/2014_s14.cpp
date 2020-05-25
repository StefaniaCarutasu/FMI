#include<iostream>
#include "Referinta.h"
#include"Electronica.h"
#include"Tiparita.h"
#include"Articol.h"
#include"Carte.h"
#include<vector>
#include<string>
using namespace std;
void meniu()
{
	cout << "-----MENIU-----\n";
	cout << "1. Pentru a introduce o noua referinta apasati 1.\n";
	cout << "2. Pentru a afisa toate referintele detinute apasati 2.\n";
	cout << "3. Pentru a afisa toate referintele tiparite intr-un anumit an apasati 3.\n";
	cout << "4. Pentru a afisa toate referintele tiparite care au numele (de familie al) unuia dintre autori egal cu un nume dat apasati 4.\n";
	cout << "5. Pentru a afisa toate referintele in format electronic care au numele proprietarului egal cu un nume dat apasati 5.\n";
	cout << "Introduceti optiunea: ";
}
void tipReferinta()
{
	cout << "-----MENIU REFERINTE-----\n";
	cout << "1. Pentru referinta electronica introduceti 1\n";
	cout << "2. Pentru articol introduceti 2\n";
	cout << "3. Pentru carte introduceti 3\n";		
	cout << "Introduceti optiunea: ";
}
int main()
{
	vector<Referinta*> referinte;
	int optiune;
	meniu();
	do
	{
		cin >> optiune;
		switch (optiune)
		{
		case 1:
		{
			int opt;
			tipReferinta();
			cin >> opt;
			while (true)
			{
				try {
					if (opt > 3 || opt < 1)
						throw "\nOptiune invalida\n";
					break;
				}
				catch (const char* s)
				{
					cout << s;
				}
			}

			switch (opt)
			{
			case 1:
			{
				Referinta* R = new Electronica;
				cin >> (*R);
				referinte.push_back(R);
				break;
			}
			case 2:
			{
				Referinta* R = new Articol;
				cin >> (*R);
				referinte.push_back(R);
				break;
			}
			case 3:
			{
				Referinta* R = new Carte;
				cin >> (*R);
				referinte.push_back(R);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 2:
		{
			for (auto ref : referinte)
				cout << *ref;
		}
		case 3:
		{
			int an; 
			cout << "Introduceti anul: ";
			cin >> an;
			for (auto ref : referinte)
			{
				if (ref->getID().find("T"))
				{
					Tiparita* ob = dynamic_cast<Tiparita*> (ref);
					if (ob->getAn() == an)
						cout << ref;
				}
			}
		}
		case 4:
		{
			string nume;
			cout << "Introduceti numele: ";
			cin >> nume;
			for (auto ref : referinte)
			{
				if (ref->getID().find("T"))
				{
					Tiparita* ob = dynamic_cast<Tiparita*> (ref);
					for(auto i: ob->getNume())
						if (i == nume)
						{
							cout << ref;
							break;
						}
				}
			}
			break;
		}
		case 5:
		{
			string nume;
			cout << "Introduceti numele proprietarului: ";
			cin >> nume;
			for (auto ref : referinte)
			{
				if (ref->getID().find("T"))
				{
					Electronica* ob = dynamic_cast<Electronica*> (ref);
					if (ob->getProprietar() == nume)
						cout << ref;
				}
			}
			break;
		}
		default:
			break;
		}
	} while (optiune);
	
	return 0;
}