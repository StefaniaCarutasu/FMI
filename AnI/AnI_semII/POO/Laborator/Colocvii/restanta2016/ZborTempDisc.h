#pragma once
#include "ZborTemporar.h"
#include "ZborCuDiscount.h"
class ZborTempDisc :
	virtual public ZborTemporar, virtual public ZborCuDiscount
{
protected:
	void readExtra(istream&);
	void displayExtra(ostream&) const;
public:
	ZborTempDisc() = default;
};

void ZborTempDisc::readExtra(istream& in)
{
	ZborTemporar::readExtra(in);
	ZborCuDiscount::readExtra(in);
}

inline void ZborTempDisc::displayExtra(ostream& out) const
{
	ZborTemporar::displayExtra(out);
	ZborCuDiscount::displayExtra(out);
}