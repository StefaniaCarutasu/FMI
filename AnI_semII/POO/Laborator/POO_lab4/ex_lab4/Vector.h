#pragma once
#include<iostream>
#include "Fraction.h"
using namespace std;
class Vector
{
	Fraction* v;
	int size, space;
public:
	Vector();	//facut
	Vector(int,int);	//facut
	~Vector();	 //facut
	void push(Fraction,int);	//facut
	Fraction pop(int);		//facut??? oare???
	bool contains(Fraction);	//facut
	void operator = (Vector);	//facut
	void operator + (Vector);  //facut
	void operator - (Vector);	//facut
	Fraction operator [] (int);
	friend ostream& operator << (ostream&, Vector&);
	friend istream& operator >> (istream&, Vector&);
	void inmultireScalar(int);
	int countGreater();
	int countLower();
};

