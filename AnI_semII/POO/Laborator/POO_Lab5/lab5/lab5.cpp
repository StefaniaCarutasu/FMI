#include <iostream>
#include "eveniment.h"
#include "evenimentColectiv.h"
#include "evenimentRecurent.h"
#include "evenimentIR.h"
#include <string>
#include <vector>
using namespace std;

int main() {

    int op;
    cout << "Dati optiune ";
    cin >> op;
    vector<eveniment> evI;
    vector<evenimentRecurent> evIR;
    vector<evenimentColectiv> evC;
    vector<evenimentGR> evCR;

    while (op == 1 || op == 2 || op == 3) {
        switch (op)
        {
        case 1:
        {
            cout << "Introduceti tipul evenimentului ";
            int tip;
            cin >> tip;
            if (tip == 1)
            {
                eveniment e;
                cin >> e;
                evI.push_back(e);
            }
            if (tip == 2)
            {
                evenimentRecurent er;
                cin >> er;
                evIR.push_back(er);
            }
            if (tip == 3)
            {
                evenimentColectiv ec;
                cin >> ec;
                evC.push_back(ec);
            }
            if (tip == 4) {
                evenimentGR ecr;
                cin >> ecr;
                evCR.push_back(ecr);
            }
            break;
        }
        case 2:
        {
            cout << "Introduceti tipul evenimentului ";
            int tip;
            cin >> tip;
            if (tip == 1)
            {
                cout << "Evenimentele individuale sunt:\n";
                for (int i = 0; i < evI.size(); i++)
                    cout << evI[i] << endl;
            }
            if (tip == 2)
            {
                cout << "Evenimentele individuale recurente sunt:\n";
                for (int i = 0; i < evIR.size(); i++)
                    cout << evIR[i] << endl;
            }
            if (tip == 3)
            {
                cout << "Evenimentele colective sunt:\n";
                for (int i = 0; i < evC.size(); i++)
                    cout << evC[i] << endl;
            }
            if (tip == 4) {
                cout << "Evenimentele colective recurente sunt:\n";
                for (int i = 0; i < evCR.size(); i++)
                    cout << evCR[i] << endl;
            }
            break;
        }
        case 3:
        {
            cout << "Introduceti tipul evenimentului ";
            string id;
            cin >> id;
            if (id.substr(0, 4) == "EV-I" && id.substr(0, 5) != "EV-IR")
            {
                for (vector<eveniment>::iterator it = evI.begin(); it != evI.end(); it++) {
                    if ((*it).getID() == id) {
                        evI.erase(it);
                        break;
                    }
                }
            }
            if (id.substr(0, 5) != "EV-IR")
            {
                for (vector<evenimentRecurent>::iterator it = evIR.begin(); it != evIR.end(); it++) {
                    if ((*it).getID() == id) {
                        evIR.erase(it);
                        break;
                    }
                }
            }
            if (id.substr(0, 4) == "EV-C" && id.substr(0, 5) != "EV-CR")
            {
                for (vector<evenimentColectiv>::iterator it = evC.begin(); it != evC.end(); it++) {
                    if ((*it).getID() == id) {
                        evC.erase(it);
                        break;
                    }
                }
            }
            if (id.substr(0, 5) != "EV-CR") {
                for (vector<evenimentGR>::iterator it = evCR.begin(); it != evCR.end(); it++) {
                    if ((*it).evenimentColectiv::getID() == id) {
                        evCR.erase(it);
                        break;
                    }
                }
            }
            break;
        }
        }
        cout << "Dati optiune ";
        cin >> op;
    }

    return 0;
}