#pragma once
#include<string>
using namespace std;
class Referinta
{
protected:
	string Titlu, ID; 
	
public:
	Referinta() { ID = "R"; }
	string getID() const { return this->ID; }
	virtual void displayExtra(ostream& out) const {}
	virtual void readExtra(istream& in) {}
	friend ostream& operator << (ostream&, const Referinta&);
	friend istream& operator >> (istream&, Referinta&);
};

ostream& operator << (ostream& out, const Referinta& R)
{
	out << "Titlul este: " << R.Titlu << '\n';
	R.displayExtra(out);
	out << '\n';
	return out;
}
istream& operator >> (istream& in, Referinta& R)
{
	cout << "Introduceti titlul referintei: ";
	in >> R.Titlu;
	R.readExtra(in);
	return in;
}

