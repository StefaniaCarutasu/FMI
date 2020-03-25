#include "Vector.h"
#include "Fraction.h"
using namespace std;

Vector::Vector()
{
	v = NULL;
	size = 0;
	space = 0;
}

Vector::Vector(int x, int s)
{
	this->space = x;
	v = new Fraction[space];
	this->size = s;
	for (int i = 0; i < s; i++)
	{
		int x, y;
		cin >> x >> y;
		v[i].setNumarator(x);
		v[i].setNumitor(y);
	}
}

Vector::~Vector()
{
	delete[] v;
	size = 0;
	space = 0;
}

void Vector::push(Fraction x, int poz)
{
	if (size == space)
	{
		Fraction* w = new Fraction[size + 5];
		for (int i = 0; i < size; i++)
			w[i] = v[i];
		delete[]v;
		v = new Fraction[size + 5];
		size++;
		space += 5;
		for (int i = 0; i < size; i++)
			v[i] = w[i];
		for (int i = size; i > poz; i--)
			v[i] = v[i - 1];
		v[poz] = x;
	}
	else
	{
		for (int i = size; i > poz; i--)
			v[i] = v[i - 1];
		v[poz] = x;
	}

}

Fraction Vector::pop(int poz)
{
	if (poz<0 || poz>size)
	{
		Fraction* aux=new Fraction;
		aux->setNumarator(-1);
		aux->setNumitor(-1);
		return *aux;
	}
	else
	{
		int i = 0;
		Fraction* aux=new Fraction;
		aux->setNumarator(v[i].getNumarator());
		aux->setNumitor(v[i].getNumitor());
		for (i = poz; i < size - 1; i++)
			v[i] = v[i + 1];
		size--;
		return *aux;
	}
	
}

bool Vector::contains(Fraction x)
{
	for (int i = 0; i < size; i++)
	{
		if (v[i].getNumarator() == x.getNumarator() && v[i].getNumitor() == x.getNumitor())
			return true;

	}
	return false;
}

void Vector::operator = (Vector Vect)
{
	if (Vect.size > this->space)
	{
		Fraction* w = new Fraction[Vect.space];
		for (int i = 0; i < size; i++)
			w[i] = v[i];
		delete[] v;
		v = new Fraction[Vect.space];
		this->space = Vect.space;
		this->size = this->space;
		for (int i = 0; i < size; i++)
			v[i] = w[i];
	}
	for (int i = 0; i < size; i++)
	{
		v[i].setNumarator(Vect[i].getNumarator());
		v[i].setNumitor(Vect[i].getNumitor());
	}
}

void Vector::operator + (Vector Vect)
{
	if (Vect.size > this->size)
	{
		for (int i = 0; i < this->size; i++)
			v[i] = v[i] + Vect[i];
	}

}
void Vector::operator - (Vector Vect)
{
	if (Vect.size > this->size)
	{
		for (int i = 0; i < this->size; i++)
			v[i] = v[i] - Vect[i];
	}

}





