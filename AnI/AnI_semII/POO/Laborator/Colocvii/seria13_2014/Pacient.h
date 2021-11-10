#pragma once
#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Pacient
{
protected:
	string nume, prenume, adresa, risc, ID;
	int varsta;
	pair<string, int> colesterol, tensiuneArteriala; //pastrez valorile sub forma de pereche data-valoare
public:
	Pacient() { ID = "NONE";}
	Pacient(int);
	string getId() const { return this->ID; }
	string getRisc() const { return this->risc; }
	string getNumeFamilie() const { return this->nume; }
	void setColesterol(int, string); //seterz valoarea impreuna cu data;
	void setTensiuneArteriala(int, string); //setez valoarea impreuna cu data
	virtual void calculareRisc();
	friend ostream& operator << (ostream&, Pacient&);
	friend istream& operator >> (istream&, Pacient&);
};

