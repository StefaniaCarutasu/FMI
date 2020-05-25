#pragma once
#include "Produs.h"
class produsLaPromotie :
	public Produs
{
	string discount;
protected:
	virtual void readExtra(istream&);
	virtual void displayExtra(ostream&) const;
};

void produsLaPromotie::readExtra(istream& in)
{
	cout << "\nIntroduceti discount-ul acordat: ";
	in >> discount;
	discount += "%";
}

void produsLaPromotie::displayExtra(ostream& out) const
{
	out << "la care s-a decis sa se adauge un discount de: " << discount;
	out << "\n";
}

