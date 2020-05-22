#pragma once
#include "Pacient.h"
class adultPeste40 :
	public Pacient
{
	string fumator, sedentarism;
public:
	adultPeste40(int);
	void calculareRisc();
	friend ostream& operator << (ostream&, adultPeste40&);
	friend istream& operator >> (istream&, adultPeste40&);
};

