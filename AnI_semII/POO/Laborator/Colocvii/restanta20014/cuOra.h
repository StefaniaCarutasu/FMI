#pragma once
#include "Angajat.h"
class cuOra :
	public Angajat
{
	string expirareContract;
protected:
	void displayExtra(ostream&) const;
	void readExtra(istream&);
public:
	cuOra() : Angajat() {}
	string getExpirare() const { return expirareContract; }
};

void cuOra::readExtra(istream& in)
{
	cout << "INTRODUCETI DATA EXPIRARII CONTRACTULUI (DD.MM.YYYY)";
	in >> expirareContract;
}

void cuOra::displayExtra(ostream& out) const
{
	if (stoi(expirareContract.substr(6)) < 15)
		out << ", PRIMA: " << prima / 2;
	else out << ", PRIMA: " << prima;
}


