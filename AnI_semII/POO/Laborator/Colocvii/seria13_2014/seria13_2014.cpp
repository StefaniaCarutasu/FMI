#include<iostream>
#include"Pacient.h"
#include"Copil.h"
#include"adultPeste40.h"
int main()
{
	vector<Pacient*> v;
	cout << "Instructiuni de utilizare:\n";
	cout << "Daca se doreste introducerea unui nou pacient introduceti 1\n";
	cout << "Daca se doreste afisarea informatiilor despre toti pacientii introduceti 2\n";
	cout << "Daca se doreste afisarea informatiilor despre toti pacientii adulti cu factor de risc introduceti 3\n";
	cout << "Daca se doreste afisarea informatiilor despre toti pacientii copii cu factor de risc introduceti 4\n";
	cout << "Daca se doreste afisarea informatiilor despre toti pacientii carea au un anumit nume de familie introduceti 5\n";
	cout << "Daca doriti sa opriti programul introduceti 0";
	int optiune, i=0;
	do
	{
		cout << "Introduceti optiunea: ";
		cin >> optiune;
		switch (optiune)
		{
		case 1:
		{
			i++;
			cout << "Ce tip de pacient doriti sa introduceti?\n";
			cout << "Pentru adult sub 40 de ani introduceti 1\n";
			cout << "Pentru adult peste 40 de ani introduceti 2\n";
			cout << "Pentru copil introduceti 3";
			int opt;
			cout << "Introduceti optiunea: ";
			cin >> opt;
			switch (opt)
			{
			case 1:
			{
				Pacient* p = new Pacient(i);
				cin >> *p;
				v.push_back(p);
				break;
			}
			case 2:
			{
				Pacient* p = new adultPeste40(i);
				cin >> *p;
				v.push_back(p);
				break;
			}
			case 3:
			{
				Pacient* p = new Copil(i);
				cin >> *p;
				v.push_back(p);
				break;
			}
			default:
				break;
			}
		}
		case 2:
		{
			for (auto it : v)
			{
				cout << it << '\n';
			}
			break;
		}
		case 3:
		{
			for (auto it : v)
			{
				if ((it->getId()).find("Adult") && it->getRisc() == "Ridicat")
					cout << it;
			}
			break;
		}
		case 4:
		{
			for (auto it : v)
			{
				if ((it->getId()).find("Copil") && it->getRisc() == "Ridicat")
					cout << it;
				break;
			}
		}
		case 5:
		{
			cout << "Introduceti numele pe care doriti sa il cautati: ";
			string numeCautat;
			cin >> numeCautat;
			for (auto it : v)
			{
				if (it->getNumeFamilie() == numeCautat)
					cout << it;
			}
		}
		default:
			cout << "Nu ati ales o optiune valida\n";
			break;
		}
	} while (optiune != 0);
	return 0;
}