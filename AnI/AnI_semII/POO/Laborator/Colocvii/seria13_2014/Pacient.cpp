#include "Pacient.h"

Pacient::Pacient(int i) { ID = to_string(i)+"Adult"; }

void Pacient::setColesterol(int valoare, string data)
{
	colesterol.first = data;
	colesterol.second = valoare;
}

void Pacient::setTensiuneArteriala(int valoare, string data)
{
	tensiuneArteriala.first = data;
	tensiuneArteriala.second = valoare;
}
void Pacient::calculareRisc()
{
	if (colesterol.second > 240 && tensiuneArteriala.second > 139)
		risc = "Ridicat";
	else if (colesterol.second > 240 || tensiuneArteriala.second > 139)
		risc = "DA";
	else risc = "NU";
}

ostream& operator << (ostream& out, Pacient& P)
{
	out << P.nume << " " << P.prenume << ": ";
	out << "Risc cardiovascular- " << P.risc << "; ";
	out << "Colesterol (" << P.colesterol.first << "): " << P.colesterol.second << " mg/dl; ";
	out << "TA (" << P.tensiuneArteriala.first << "): " << P.tensiuneArteriala.second << '\n';
	return out;
}

istream& operator >> (istream& in, Pacient& P)
{
	in >> P.nume >> P.prenume >> P.varsta >> P.adresa;
	return in;
}