#include "DFA.h"

DFA::DFA() 
{
	this->q0 = 0;
	partitii = NULL;
}
DFA::DFA(set<int> Q, set<char> Sigma, map<pair<int, char>, int> delta, int q0, set<int> F)
{
	this->Q = Q;
	this->Sigma = Sigma;
	this->delta = delta;
	this->q0 = q0;
	this->F = F;
	
}

int DFA::getInitialState() { return this->q0; }
set<int> DFA::getFinalState() { return this->F; }
set<int> DFA::getStates() {	return this->Q; }
set<char> DFA::getSigma() { return this->Sigma; }
map<pair<int, char>, int> DFA::getDelta() { return this->delta; }

istream& operator >> (istream& f, DFA& M)
{
	int noOfStates;
	f >> noOfStates;
	for (int i = 0; i < noOfStates; ++i)
	{
		int q;
		f >> q;
		M.Q.insert(q);
	}

	int noOfLetters;
	f >> noOfLetters;
	for (int i = 0; i < noOfLetters; ++i)
	{
		char ch;
		f >> ch;
		M.Sigma.insert(ch);
	}

	int noOfTransitions;
	f >> noOfTransitions;
	for (int i = 0; i < noOfTransitions; ++i)
	{
		int s, d;
		char ch;
		f >> s >> ch >> d;
		M.delta[{s, ch}] = d;
	}

	f >> M.q0;

	int noOfFinalStates;
	f >> noOfFinalStates;
	for (int i = 0; i < noOfFinalStates; ++i)
	{
		int q;
		f >> q;
		M.F.insert(q);
	}

	return f;
}
void DFA::initializarePartitii()   //partitii este o matrice care va fi completata doar sub diagonala principala 
{
	partitii = new int* [this->Q.size() - 1];
	for (int i = 0; i < this->Q.size(); i++)
		partitii[i] = new int[this->Q.size() - 1];
	for (int i = 0; i < this->Q.size(); i++)
		for (int j = 0; j < this->Q.size(); j++)
			partitii[i][j] = 0;

	for (auto i : this->getFinalState())  //initial marcam cu 1 perechile (i,j) unde i este stare finala si j nu este sau invers
	{
		for (auto j : this->getStates())
			if (isFinalState(j) == false)
			{
				if (i < j)
					partitii[j][i] = 1;
				else partitii[i][j] = 1;
			}
	}
}
int** DFA::getPartitii() { return this->partitii; }

bool DFA::isFinalState(int q)
{
	return F.find(q) != F.end();
}

void DFA::Partitii() 
{
	int ok = 0;
	for(auto i: this->getStates())  //pentru fiecare stare a automatului
		for (auto j : this->getStates())	//pentru fiecare stare a automatului
			for (auto a : this->getSigma())	//pentru fiecare litera a alfabetului
			{
				if (i != j && (partitii[i][j]==0 && partitii[j][i]==0))	//daca cele 2 stari sunt diferite si inca nu a fost verificat daca fac parte din aceeasi partitie
				{
					pair<int, int > p = { getDelta()[{i,a}], getDelta()[{j,a}] };	//p este perechea formata din starile in care ajung i si j cu litera a
					if (partitii[p.first][p.second] == 1 || partitii[p.second][p.first] == 1)	//daca aceasta pereche este marcata in matrice atunci marcam si perechea (i,j)
					{
						if (i < j)  //vreau sa marchez doar sub diagonala principala
							partitii[j][i] = 1;
						else partitii[i][j] = 1;
						ok = 1;
					} 			
				}
			}
	if (ok == 1)
	{
		ok = 0;
		Partitii();  //daca a fost facuta o modificare atunci mai executam inca o data algoritmul
	}
}

void DFA::minimizareDFA()
{
	Partitii();
	int l =this->getStates().size();
	set<set<int>> states;  //multimea partitiilor
	set<int> p;   //in p voi retine fiecare partitie in parte
	for(int i=0; i<l; i++)
	{
		p.insert(i);	//adaugam i la partitie
			for (auto j: this->getStates())
			{
				if (partitii[i][j] == 0 && i > j && i!=j)	//toate starile de pe coloana lui i care sunt marcate cu 0 in matrice vor fi in aceeasi partitie cu i
					p.insert(j);
			}
			if (p.size() > 0)	
			{
				states.insert(p);	//adaug noua partitie la multime
				p.clear();	//eliberez p pentru a-l putea reutiliza pentru urmatoarea stare din Q
			}
	}

	//este posibil ca o stare sa imi apara atat singura cat si in partitie (starea q0 in special) asa ca daca se intampla asta atunci o scoatem din multimea de stari
	set<set<int>> states1;
	for (auto i : states)	//pt fiecare set din setul mare
		if (i.size() == 1)	//daca setul are exact un element
		{
			int ok = 0;
				for (auto j : states)	//pentru fiecare set din setul mare
					if (j.find(*i.begin()) != j.end() && j.size() >= 2)		//verific daca elementul se afla in alt set de lungime mai mare decat 1
						ok = 1;
			if (ok == 0)
				states1.insert(i);	//daca nu mai apare o adaugam la noua multime
		}
		else states1.insert(i);		//orice partitie cu mai mult de un element este adaugata automat la noua multime
	states.clear();
	states = states1;
				
	cout << "Starile sunt: ";
	for (auto i : states)
	{
		cout << "( ";
		for (auto j : i)
			cout << j << " ";
		cout << ") ";
	}
	cout << '\n';
	cout << "Starea initiala este: ";	//partitia care contine starea initiala
	for (auto& i : states)
	{
		int ok = 0;
		for (auto j : i)
		{
			if (j == this->q0)
			{
				ok = 1;
				break;
			}
		}
		if (ok)
		{
			cout << "( ";
			for (auto j : i)
				cout << j << " ";
			cout << ")";
		}
	}
	cout << '\n';

	cout << "Alfabetul este: ";		//acelasi alfabet ca DFA ul initial
	for (auto a : this->getSigma())
		cout << a << " ";
	cout << '\n';

	cout << "Starile finale sunt: ";	//partitiile care au stari finale ale DFA ului initial
	for(auto i: states)
	{
		int ok = 0;
		for (auto j : i)
		{
			if (this->isFinalState(j) == true)
				ok = 1;
			if (ok)
				break;
		}
		if (ok)
		{
			cout << "(";
			for (auto j : i)
				cout << j << " ";
			cout << ") ";
		}
	}
	cout << '\n';

	cout << "Starea din care pleaca" << "     " << "litera" << "     " << "starea in care ajunge"<<'\n';
	for (auto i : states)
	{
		for (auto a : this->getSigma())
		{
			for (auto j : i)
				cout << j << " "; // de unde pleaca
			cout << "                           ";
			cout << a << "                     ";  //litera
			int ok = 0;
			for (auto k : states) // unde ajunge
			{
				for (auto j : k)
				{
					if (j == this->getDelta()[{*i.begin(), a}])
					{
						ok = 1;
						break;
					}
				}
				if (ok)
				{
					for (auto j : k)
						cout << j << " ";
					break;
				}
			}
			cout << '\n';

		}
	}
}