#include "evenimentRecurent.h"

evenimentRecurent::evenimentRecurent() {
    this->ID = "EV-IR" + to_string(count);
    recurenta = "";
}

istream& operator>>(istream& in, evenimentRecurent& e) {
    in >> e.nume;
    in >> e.data.minut >> e.data.ora >> e.data.zi >> e.data.luna >> e.data.an;
    in >> e.locatie;
    in >> e.durata;
    in >> e.recurenta;

    return in;
}

ostream& operator<< (ostream& out, const evenimentRecurent e) {
    out << "Nume: " << e.nume << endl;
    out << "Ora si data: " << e.data.ora << ":" << e.data.minut << ", "
        << e.data.zi << "/" << e.data.luna << "/" << e.data.an << endl;
    out << "Locatie: " << e.locatie << endl;
    out << "ID: " << e.ID << endl;
    out << "Durata: " << e.durata << " minute" << endl;
    out << "Eveniment " << e.recurenta << endl;
    return out;
}
