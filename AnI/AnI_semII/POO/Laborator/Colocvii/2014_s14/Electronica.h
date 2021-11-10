#pragma once
#include "Referinta.h"
class Electronica :
	public Referinta
{
	string numeProprietar, URL, dataAccesarii;
public:
	Electronica() : Referinta() { ID += "E"; }
	string getProprietar() const { return numeProprietar; }
protected:
	void readExtra(istream&);
	void displayExtra(ostream&) const;
};

void Electronica::readExtra(istream& in)
{
	cout << "Introduceti numele proprietarului: ";
	in >> numeProprietar;
	cout << '\n';
	cout << "Introduceti URL-ul: ";
	in >> URL;
	cout << '\n';
	cout << "Introduceti data ultimei accesari sub forma DD.MM.YYYY hh:mm: ";
	in.get();
	getline(in, dataAccesarii);
}
void Electronica::displayExtra(ostream& out) const
{
	out << "Propritar: " << numeProprietar;
	out << "; URL: " << URL;
	out << "; (" << dataAccesarii << ")";
}

