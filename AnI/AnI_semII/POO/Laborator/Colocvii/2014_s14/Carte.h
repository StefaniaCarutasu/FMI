#pragma once
#include "Tiparita.h"
class Carte :
	public Tiparita
{
	string numeOrasEditura;
	void readExtra(istream&);
	void displayExtra(ostream&) const;
public:
	Carte() : Tiparita() { ID += "C"; }
};
void Carte::readExtra(istream& in)
{
	Tiparita::readExtra(in);
	cout << "Introduceti orasul unde a fost tiparita: ";
	in >> numeOrasEditura;
}

void Carte::displayExtra(ostream& out) const
{
	Tiparita::displayExtra(out);
	out << "Orasul unde a fost tiparita este: " << numeOrasEditura;
	out << '\n';
}


