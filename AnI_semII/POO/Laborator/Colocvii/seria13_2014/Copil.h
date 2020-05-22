#pragma once
#include "Pacient.h"
class Copil :
	public Pacient
{
	string numeMama, numeTata, antecedente;
	pair<string, double> proteinaReactivaC;
public:
	Copil(int);
	void setProteina(string, double);
	void calculareRisc();
	friend ostream& operator << (ostream&, Copil&);
	friend istream& operator >> (istream&, Copil&);
};

