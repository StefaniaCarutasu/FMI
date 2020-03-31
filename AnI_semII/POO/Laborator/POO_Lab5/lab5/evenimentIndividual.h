#pragma once
#include <iostream>
#include <string>
#include"eveniment.h"

using namespace std;

class evenimentIndividual: public eveniment
{
protected:
	string participant;
public:
	evenimentIndividual();
	friend istream& operator>>(istream&, evenimentIndividual&);
	friend ostream& operator<<(ostream&, const evenimentIndividual);
};

