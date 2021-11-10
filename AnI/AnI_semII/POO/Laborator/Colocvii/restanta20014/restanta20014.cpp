#include<iostream>
#include"Angajat.h"
#include"cuOra.h"
#include"lucrativPermanent.h"
#include"tesaPermanent.h"
#include<vector>
using namespace std;
void meniu()
{
	cout << "-----Meniu-----\n";
	cout << "Pentru a introduce un nou angajat apasati 1\n";
	cout << "Pentru afisarea tuturor angajatilor apasati 2\n";
	cout << "Pentru afisarea tuturor angajatilor lucrativi permanenti care au copii minori in ingrijire apasati 3\n";
	cout << "Pentru afisarea tuturor angajatilor care isi fac rezervare la munte in al doilea weekend din decembrie apasati 4\n";
	cout << "Pentru afisarea tuturor angajatilor în regim de plata cu ora, care au contract pana cel putin in martie 2015 apasati 5\n ";
	cout << "Daca dorit oprirea programului introduceti 0\n";
}
void meniuAng()
{
	cout << "Pentru TESA permanent introduceti 1\n";
	cout << "Pentru lucrativ permanent introduceti 2\n";
	cout << "Pentru lucrator cu ora introduceti 3\n";
}
int main()
{
	vector<Angajat*> ang;
	int optiune;
	meniu();
	do
	{
		cout << "Optiunea: ";
		cin >> optiune;
		switch (optiune)
		{
		case 1:
		{
			int opt;
			cout << "optiunea: ";
			cin >> opt;
			switch (opt)
			{
			case 1:
			{
				Angajat* nou = new tesaPermanent;
				cin >> (*nou);
				ang.push_back(nou);
				break;
			}
			case 2:
			{
				Angajat* nou = new lucrativPermanent;
				cin >> (*nou);
				ang.push_back(nou);
				break;
			}
			case 3:
			{
				Angajat* nou = new cuOra;
				cin >> (*nou);
				ang.push_back(nou);
				break;
			}
			default:
				break;
			}
			break;
		}
		case 2:
		{
			for (auto ag : ang)
				cout << (*ag);
			break;
		}
		case 3:
		{
			for (auto ag : ang)
			{
				if (ag->getActivitate().find("lucrativ"))
				{
					lucrativPermanent* ob = dynamic_cast<lucrativPermanent*> (ag);
					if (ob->getMinori() > 0)
						cout << (*ag);
				}
			}
			break;
		}
		case 4:
		{
			for (auto ag : ang)
			{
				if (ag->getActivitate().find("TESA"))
				{
					tesaPermanent* ob = dynamic_cast<tesaPermanent*> (ag);
					if (ob->getWeekend() == 2)
						cout << (*ag);
				}
			}
			break;
		}
		case 5:
		{
			for (auto ag : ang)
			{
				if (ag->getActivitate().find("ora"))
				{
					cuOra* ob = dynamic_cast<cuOra*> (ag);
					if (stoi(ob->getExpirare().substr(ob->getExpirare().size() - 3, ob->getExpirare().size() - 1)) < 15)
						if (stoi(ob->getExpirare().substr(3, 4)) >= 3)
							cout << (*ag);
				}
			}
			break;
		}
		default:
			break;
		}
	} while (optiune > 0);
	return 0;
}