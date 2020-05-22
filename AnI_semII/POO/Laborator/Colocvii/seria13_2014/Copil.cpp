#include "Copil.h"
Copil::Copil(int i)
{
	ID = to_string(i)+"Copil";
}

void Copil::setProteina(string data, double valoare)
{
	proteinaReactivaC = make_pair(data, valoare);
}

void Copil::calculareRisc()
{
	int r = 0;
	if (Pacient::colesterol.second > 240)
		r++;
	if (Pacient::tensiuneArteriala.second > 139)
		r++;
	if (antecedente == "DA")
		r++;
	if (proteinaReactivaC.second > 0.6)
		r++;
	if (Pacient::risc == "DA")
		r++;
	if (Pacient::risc == "Ridicat")
		r += 2;
	if (r >= 2)
		Pacient::risc = "Ridicat";
	else if (r == 1)
		Pacient::risc = "DA";
	else Pacient::risc = "NU";
}

ostream& operator << (ostream& out, Copil& C)
{
	out << C.Pacient::nume << " " << C.Pacient::prenume << ": ";
	out << "Risc cardiovascular- " << C.Pacient::risc << "; ";
	out << "Colesterol (" << C.Pacient::colesterol.first << "): " << C.Pacient::colesterol.second << " mg/dl; ";
	out << "TA (" << C.Pacient::tensiuneArteriala.first << "): " << C.Pacient::tensiuneArteriala.second << '\n';
	out << "Proteina C reactiva (" << C.proteinaReactivaC.first << "): " << C.proteinaReactivaC.second << "mg/dl; ";
	out << "Antecedente in famillie: " << C.antecedente;
	return out;

}

istream& operator >> (istream& in, Copil& C)
{
	in >> C.nume >> C.prenume >> C.varsta >> C.adresa >> C.numeMama >> C.numeTata >> C.antecedente;
	return in;
}