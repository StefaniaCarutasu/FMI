#pragma once
#include<string>
#include<iostream>
using namespace std;
class Produs
{
protected:
	string unitateMasura, tipProdus;
	float pret;
	virtual void readExtra(istream& in) {}
	virtual void displayExtra(ostream& out) const {}
public:
	Produs();
	friend ostream& operator << (ostream&, Produs&);
	friend istream& operator >> (istream&, Produs&);
};

istream& operator >> (istream& in, Produs& P)
{
	string masura;
	cout << "Introduceti tipul de produs: ";
	in >> P.tipProdus;
	cout << "Introduceti unitatea de masura (bucata/greutate/volum): ";
	in >> masura;
	if (masura == "bucata")
		P.unitateMasura = "bucati";
	else if (masura == "greutate")
		P.unitateMasura = "kg";
	else P.unitateMasura = "litri";
	cout << '\n' << "Pretul este: ";
	in >> P.pret;
	P.readExtra(in);
	return in;
}

ostream& operator << (ostream& out, Produs& P)
{
	out << P.unitateMasura << " de " << P.tipProdus << '\n';
	P.displayExtra(out);
	return out;
}




