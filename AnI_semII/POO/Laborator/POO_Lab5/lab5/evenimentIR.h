#pragma once
#include "evenimentColectiv.h"
#include "evenimentRecurent.h"
#include<iostream>
#include<string>
using namespace std;

class evenimentGR :
	public evenimentColectiv, public evenimentRecurent
{
;
public:
	evenimentGR();
	friend ostream& operator << (ostream&, const evenimentGR);
	friend istream& operator >> (istream&, evenimentGR&);
};

