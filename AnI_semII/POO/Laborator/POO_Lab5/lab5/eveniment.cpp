#include "eveniment.h"


unsigned eveniment::count = 0;

eveniment::eveniment() {
    count++;
    this->ID = "EV-I" + to_string(count);
}

eveniment::eveniment(const string n, const string l, const Data dt, const unsigned dr) :
    eveniment()
{
    nume = n;
    data = dt;
    locatie = l;
    durata = dr;
}
string eveniment::getID() {
    return this->ID;
}

ostream& operator<< (ostream& out, const eveniment& e) {
    out << "Nume: " << e.nume << endl;
    out << "Ora si data: " << e.data.ora << ":" << e.data.minut << ", "
        << e.data.zi << "/" << e.data.luna << "/" << e.data.an << endl;
    out << "Locatie: " << e.locatie << endl;
    out << "ID: " << e.ID << endl;
    out << "Durata: " << e.durata << " minute" << endl;
    return out;
}

istream& operator>> (istream& in, eveniment& e) {
    in >> e.nume;
    in >> e.data.minut >> e.data.ora >> e.data.zi >> e.data.luna >> e.data.an;
    in >> e.locatie;
    in >> e.durata;
    return in;
}