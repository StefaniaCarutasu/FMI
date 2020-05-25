#pragma once
#include "Zbor.h"
class ZborCuDiscount :
	virtual public Zbor
{
protected:
	int discount;
	virtual void readExtra(istream&);
	virtual void displayExtra(ostream&) const;
public:
	ZborCuDiscount() = default;
};

void ZborCuDiscount::readExtra(istream& in)
{
	in >> discount;
}
inline void ZborCuDiscount::displayExtra(ostream& out) const
{
	out << discount;
}