#include <iostream>
#include "Zbor.h"
#include"ZborCuDiscount.h"
#include"ZborTempDisc.h"
#include"ZborTemporar.h"
#include<vector>
#include<map>
using namespace std;
int main()
{
    map<pair<string, string>, vector<Zbor*>> rute;
    int optiune;
    do
    {
        cin >> optiune;
        switch (optiune)
        {
        case 1: //adaugare ruta
        {
            string plecare, sosire;
            cin.get();
            getline(cin, plecare);
            cin.get();
           getline(cin, sosire);
            vector<Zbor*> z;
            rute[make_pair(plecare, sosire)] = z;
            break;
        }
        case 2: //afisare toate rutele
        {
            for (auto i : rute)
                cout << i.first.first << " " << i.first.second;
            break;
        }
        case 3: // zbor pe ruta
        {
            int tip;
            cin >> tip;
            switch (tip)
            {
            case 1:
            {
                Zbor* zb = new Zbor;
                cin >> *zb;
                bool gasit = false;
                for (auto i : rute)
                    if (i.first.first == zb->getPlecare() && i.first.second == zb->getSosire())
                    {
                        i.second.push_back(zb);
                        gasit = true;
                        break;
                    }
                if (!gasit)
                    rute[make_pair(zb->getPlecare(), zb->getSosire())].push_back(zb);
                break;
            }
            case 2:
            {
                Zbor* zb = new ZborTemporar;
                cin >> *zb;
                bool gasit = false;
                for (auto i : rute)
                    if (i.first.first == zb->getPlecare() && i.first.second == zb->getSosire())
                    {
                        i.second.push_back(zb);
                        gasit = true;
                        break;
                    }
                if (!gasit)
                    rute[make_pair(zb->getPlecare(), zb->getSosire())].push_back(zb);
                break;
            }
            case 3:
            {
                Zbor* zb = new ZborCuDiscount;
                cin >> *zb;
                bool gasit = false;
                for (auto i : rute)
                    if (i.first.first == zb->getPlecare() && i.first.second == zb->getSosire())
                    {
                        i.second.push_back(zb);
                        gasit = true;
                        break;
                    }
                if (!gasit)
                    rute[make_pair(zb->getPlecare(), zb->getSosire())].push_back(zb);
                break;
            }
            case 4:
            {
                Zbor* zb = new ZborTempDisc;
                cin >> *zb;
                bool gasit = false;
                for (auto i : rute)
                    if (i.first.first == zb->getPlecare() && i.first.second == zb->getSosire())
                    {
                        i.second.push_back(zb);
                        gasit = true;
                        break;
                    }
                if (!gasit)
                    rute[make_pair(zb->getPlecare(), zb->getSosire())].push_back(zb);
                break;
            }
            default:
                break;
            }
            break;
        }
        case 4: //curse intre 2 date calendaristice
        {
            int data1, data2;
            cin >> data1 >> data2;
            for (auto i : rute)
                for (auto j : i.second)
                    if (data1<j->getZiPlecare() && data2>j->getZiPlecare())
                        cout << *j;
        }
        case 5://curse active
        {

        }
        case 6:
        {
            for(auto i: rute)
                for (auto j : i.second)
                {
                    ZborTempDisc* ob = dynamic_cast<ZborTempDisc*> (j);
                    if (ob == NULL)
                        cout << i.first.first << " " << i.first.second << '\n';
                    else
                    {
                        ZborCuDiscount* ob = dynamic_cast<ZborCuDiscount*> (j);
                        if(ob == NULL)
                            cout << i.first.first << " " << i.first.second << '\n';
                    }
                }
        }
        default:
            break;
        }
    } while (optiune);
}