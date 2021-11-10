#pragma once
#include<vector>
#include "Referinta.h"
class Tiparita :
	public Referinta
{
protected:
	vector<string> numeAutori, prenumeAutori;
	int anulPublicarii;
	virtual void readExtra(istream&);
	virtual void displayExtra(ostream&) const;
public:
	Tiparita() : Referinta() { ID += "T"; };
	int getAn() const { return anulPublicarii; };
	vector<string> getNume() const { return numeAutori; }
};

void Tiparita::readExtra(istream& in)
{
	cout << "Introduceti anul publicarii: ";
	in >> anulPublicarii;
	cout << "Introduceti un autor: ";
	int i;
	do
	{
		string nume;
		cout << "Nume familie: ";
		in >> nume;
		numeAutori.push_back(nume);
		cout << '\n';
		cout << "Prenume: ";
		in.get();
		getline(in, nume);
		prenumeAutori.push_back(nume);
		cout << "Daca doriti sa mai introduceti autori, apasati 1: ";
		in >> i;
	} while (i == 1);

}

void Tiparita::displayExtra(ostream& out) const
{
	out << "Numele autorilor: ";
	for (auto i : numeAutori)
		out << i << ", ";
	out << '\n' << "Anul publicarii este: " << anulPublicarii;
	out << '\n';
}

