#include "evenimentIndividual.h"

evenimentIndividual::evenimentIndividual()
{
	this->ID = "EV-I" + to_string(count);
    this->participant = "";
}

istream& operator>>(istream& in, evenimentIndividual& e)
{
    in >> e.nume;
    in >> e.data.minut >> e.data.ora >> e.data.zi >> e.data.luna >> e.data.an;
    in >> e.locatie;
    in >> e.durata;
    in >> e.participant;
    return in;
}

ostream& operator<< (ostream& out, const evenimentIndividual e)
{
    out << "Nume: " << e.nume << endl;
    out << "Ora si data: " << e.data.ora << ":" << e.data.minut << ", "
        << e.data.zi << "/" << e.data.luna << "/" << e.data.an << endl;
    out << "Locatie: " << e.locatie << endl;
    out << "ID: " << e.ID << endl;
    out << "Durata: " << e.durata << " minute" << endl;
    out << "Participant: ";
    out << e.participant;
    return out;

}