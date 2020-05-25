#pragma once
#include "Angajat.h"
class tesaPermanent :
	public Angajat
{
	int weekend;
protected:
	void displayExtra(ostream&) const;
	void readExtra(istream&);
public:
	tesaPermanent(): Angajat() {}
	int getWeekend() const { return weekend; }
};
void tesaPermanent::readExtra(istream& in)
{
	cout << "ALEGETI UN WEEKEND: ";
	in >> weekend;
}
void tesaPermanent::displayExtra(ostream& out) const
{
	out << "\nTIP ACTIVITATE: " << tipActivitate;
	out << "\nWEEKEND ALES: " << weekend;
	out << "\nPRIMA: " << Angajat::prima<<" RON";
}
