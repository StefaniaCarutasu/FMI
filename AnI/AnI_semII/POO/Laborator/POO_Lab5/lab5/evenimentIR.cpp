#include "evenimentIR.h"

evenimentGR::evenimentGR()
{
	this->evenimentColectiv::ID= "EV-GR" + to_string(count);
	this->evenimentColectiv::ID = "";
}

 ostream& operator << (ostream& out, const evenimentGR e)
{
     out << "Nume: " << e.evenimentColectiv::nume << endl;
     out << "Ora si data: " << e.evenimentColectiv::data.ora << ":" << e.evenimentColectiv::data.minut << ", "
         << e.evenimentColectiv::data.zi << "/" << e.evenimentColectiv::data.luna << "/" << e.evenimentColectiv::data.an << endl;
     out << "Locatie: " << e.evenimentColectiv::locatie << endl;
     out << "ID: " << e.evenimentColectiv::ID << endl;
     out << "Durata: " << e.evenimentColectiv::durata << " minute" << endl;
     out << "Participanti: ";
     for (string a : e.evenimentColectiv::participanti)
     {
         out << a << ", ";
     }
     return out;
}

 istream& operator >> (istream& in, evenimentGR& e)
 {
     in >> e.evenimentColectiv::nume;
     in >> e.evenimentColectiv::data.minut >> e.evenimentColectiv::data.ora >> e.evenimentColectiv::data.zi >> e.evenimentColectiv::data.luna >> e.evenimentColectiv::data.an;
     in >> e.evenimentColectiv::locatie;
     in >> e.evenimentColectiv::durata;
     int nrParticipanti;
     in >> nrParticipanti;
     string a;
     for (int i = 0; i < nrParticipanti; i++)
     {
         in >> a;
         e.participanti.push_back(a);
     }
     return in;
 }
