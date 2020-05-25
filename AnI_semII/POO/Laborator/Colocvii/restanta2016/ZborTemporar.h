#pragma once
#include "Zbor.h"
class ZborTemporar :
	virtual public Zbor
{
protected:
	string unitateMasura;
	int prelungire;
	virtual void readExtra(istream&);
	virtual void displayExtra(ostream&) const;
public:
	ZborTemporar() = default;
};

void ZborTemporar::readExtra(istream& in)
{
	in >> prelungire >> unitateMasura;
}
inline void ZborTemporar::displayExtra(ostream& out) const
{
	out << prelungire << unitateMasura;
}