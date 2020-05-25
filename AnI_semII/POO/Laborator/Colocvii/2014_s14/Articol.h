#pragma once
#include "Tiparita.h"

class Articol :
	public Tiparita
{
	vector<pair<int,string>> numarNumePagini;
	int nrPagini, paginaInceput;
	void readExtra(istream&);
	void displayExtra(ostream&) const;
public:
	Articol() :Tiparita() { ID += "A"; nrPagini = 0; }
};

void Articol::readExtra(istream& in)
{
	Tiparita::readExtra(in);
	cout << "Introduceti numarul paginilor: ";
	in >> nrPagini;
	cout << "Introduceti pagina la care incepe articolul: ";
	in >> paginaInceput;
	for (int i = 0; i < nrPagini; i++)
	{
		string s;
		cout << "Pagina curenta: " << paginaInceput+i << ". Introduceti numele paginii: ";
		in.get();
		getline(in, s);
		numarNumePagini.push_back(make_pair(paginaInceput+i, s));
	}
}

void Articol::displayExtra(ostream& out) const
{
	Tiparita::displayExtra(out);
	out << "Numar pagini: " << nrPagini << '\n';
	for (auto i : numarNumePagini)
		out << "Pagina " << i.first << "se numeste: " << i.second;
}

