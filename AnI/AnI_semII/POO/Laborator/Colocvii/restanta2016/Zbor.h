#pragma once
#include<iostream>
#include<string>
using namespace std;
class Zbor
{
protected:
	string ID, plecare, sosire;
	int ziPlecare, durata, pret;
	virtual void readExtra(istream& in) {}
	virtual void displayExtra(ostream& out) const { }
public:
	Zbor() = default;
	string getPlecare() { return plecare; }
	string getSosire() { return sosire; }
	int getZiPlecare() { return ziPlecare; }
	friend istream& operator >> (istream&, Zbor&);
	friend ostream& operator << (ostream&, const Zbor&);
};

istream& operator>>(istream& in, Zbor& Z)
{
	in >> Z.ID;
	in.get();
	getline(in, Z.plecare);
	in.get();
	getline(in, Z.sosire);
	in >> Z.durata >> Z.ziPlecare >> Z.pret;
	Z.readExtra(in);
	return in;
}

inline ostream& operator<<(ostream& out, const Zbor& Z)
{
	out << Z.ID << Z.ziPlecare << Z.plecare << Z.sosire << Z.durata<<Z.pret;
	Z.displayExtra(out);
	return out;
}
	