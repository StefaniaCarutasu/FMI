#pragma once
#include<string>
#include<iostream>
using namespace std;
class Angajat
{
protected:
	string nume, prenume, tipContract, dataInceput, tipActivitate;
	int prima;
	virtual void displayExtra(ostream& out) const {}
	virtual void readExtra(istream& in) {}
public:
	Angajat() { prima = 0; }
	string getActivitate() { return tipActivitate; }
	void setPrima(int prima) { this->prima = prima; }
	friend ostream& operator << (ostream&, const Angajat&);
	friend istream& operator >> (istream&, Angajat&);
};

istream& operator >> (istream& in, Angajat& A)
{
	cout << "NUME: ";
	in >> A.nume;
	cout << "PRENUME: ";
	in >> A.prenume;
	cout << "TIP CONTRACT (contract permanent/plata cu ora): ";
	in.get();
	getline(in, A.tipContract);
	cout << "DATA DE INCEPUT (DD.MM.YYYY): ";
	in.get();
	getline(in, A.dataInceput);
	cout << "TIP ACTIVITATE (TESA/lucrativ): ";
	in >> A.tipActivitate;
	A.readExtra(in);
	return in;
}

ostream& operator << (ostream& out, const Angajat& A) 
{
	out << A.nume << " " << A.prenume << ", " << A.tipContract << ", " << A.dataInceput << "-";
	A.displayExtra(out);
	return out;
}
