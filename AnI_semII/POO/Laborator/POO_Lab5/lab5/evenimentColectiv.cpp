#include "evenimentColectiv.h"

evenimentColectiv::evenimentColectiv() {
    this->ID = "EV-G" + to_string(count);

}

istream& operator>>(istream& in, evenimentColectiv& e) {
    in >> e.nume;
    in >> e.data.minut >> e.data.ora >> e.data.zi >> e.data.luna >> e.data.an;
    in >> e.locatie;
    in >> e.durata;
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


ostream& operator<< (ostream& out, const evenimentColectiv e) {
    out << "Nume: " << e.nume << endl;
    out << "Ora si data: " << e.data.ora << ":" << e.data.minut << ", "
        << e.data.zi << "/" << e.data.luna << "/" << e.data.an << endl;
    out << "Locatie: " << e.locatie << endl;
    out << "ID: " << e.ID << endl;
    out << "Durata: " << e.durata << " minute" << endl;
    out << "Participanti: ";
    for (string a : e.participanti)
    {
        out << a << ", ";
    }
    return out;
}
