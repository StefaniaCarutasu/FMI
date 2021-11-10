#pragma once
#include "Produs.h"
class produsPerisabil :
	public Produs
{
protected:
	string termenValabilitate;
	virtual void readExtra(istream&);
	virtual void displayExtra(ostream&) const;
public:
	produsPerisabil(): Produs() {}
};

void produsPerisabil::readExtra(istream& in)
{
	cout << "\nIntroduceti termenul de valabilitate: ";
	in >> termenValabilitate;
	termenValabilitate += " zile";
}

void produsPerisabil::displayExtra(ostream& out) const
{
	out << " " << termenValabilitate;
}

