#include "adultPeste40.h"
adultPeste40::adultPeste40(int i) 
{
	this->ID = to_string(i) + "AdultPeste40";
}

void adultPeste40::calculareRisc()
{
	int r = 0;
	if (Pacient::colesterol.second > 240)
		r++;
	if (Pacient::tensiuneArteriala.second > 139)
		r++;
	if (fumator == "DA")
		r++;
	if (sedentarism == "Ridicat")
		r++;
	if (r >= 2)
		Pacient::risc = "Ridicat";
	else if (r >= 1)
		Pacient::risc = "DA";
	else Pacient::risc = "NU";
}

ostream& operator <<(ostream& out, adultPeste40& A)
{
	out << A.Pacient::nume << " " << A.Pacient::prenume << ": ";
	out << "Risc cardiovascular- " << A.Pacient::risc << "; ";
	out << "Colesterol (" << A.Pacient::colesterol.first << "): " << A.Pacient::colesterol.second << " mg/dl; ";
	out << "TA (" << A.Pacient::tensiuneArteriala.first << "): " << A.Pacient::tensiuneArteriala.second << '\n';
	out << "Fumator: " << A.fumator << "; Sedentarism:  " << A.sedentarism;
	return out;
}

istream& operator >> (istream& in, adultPeste40& P)
{
	in >> P.nume >> P.prenume >> P.varsta >> P.adresa >> P.fumator >> P.sedentarism;
	return in;
}