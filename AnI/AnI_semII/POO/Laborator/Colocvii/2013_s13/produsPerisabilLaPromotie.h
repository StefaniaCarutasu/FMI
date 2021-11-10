#pragma once
#include "produsPerisabil.h"
#include "produsLaPromotie.h"
class produsPerisabilLaPromotie :
	public produsPerisabil, public produsLaPromotie
{
protected:
	void readExtra(istream&);
	void displayExtra(ostream&) const;
public:
	produsPerisabilLaPromotie(): produsLaPromotie() {}
};

void produsPerisabilLaPromotie::readExtra(istream& in)
{
	produsPerisabil::readExtra(in);
	produsLaPromotie::readExtra(in);
}

void produsPerisabilLaPromotie::displayExtra(ostream& out) const
{
	produsPerisabil::displayExtra(out);
	produsLaPromotie::displayExtra(out);
}
