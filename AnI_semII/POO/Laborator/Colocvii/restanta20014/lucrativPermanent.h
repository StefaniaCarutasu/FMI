#pragma once
#include "Angajat.h"
class lucrativPermanent :
	public Angajat
{
	int nrMinori;
protected:
	void displayExtra(ostream&) const;
	void readExtra(istream&);
public:
	int getMinori() const { return nrMinori; }
	lucrativPermanent() : Angajat() {}
};

void lucrativPermanent::readExtra(istream& in)
{
	cout << "NUMAR MINORI: ";
	in >> nrMinori;
}

void lucrativPermanent::displayExtra(ostream& out) const
{
	out << ", TIP ACTIVITATE: " << tipActivitate;
	out << ", NUMAR MINORI: " << nrMinori;
	string anInceput = dataInceput.substr(dataInceput.size() - 5, dataInceput.size() - 1);
	int procent = 2015 - stoi(anInceput);
	int primaAng = procent / 100 * prima * nrMinori;
	out << ", PRIMA: " << prima + primaAng << "RON";
}

