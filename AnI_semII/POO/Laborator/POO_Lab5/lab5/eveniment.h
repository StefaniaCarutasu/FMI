#pragma once                                                                                    
#include <iostream>
#include <string>

using namespace std;


class eveniment {
public:
    struct Data {
        unsigned minut, ora, zi, luna, an;
    };

protected:
    string nume;
    Data data;
    string locatie;
    string ID;
    unsigned durata; // in minute
    static unsigned count;

public:
    eveniment();
    eveniment(const string, const string, const Data, const unsigned = 60);
    string getID();
    friend ostream& operator<< (ostream&, const eveniment&);
    friend istream& operator>> (istream&, eveniment&);
};

