#pragma once
#include<string>
#include<iostream>
#include "eveniment.h"
using namespace std;
class evenimentRecurent : public eveniment {
protected:
    string recurenta;
public:
    evenimentRecurent();
    friend istream& operator>>(istream&, evenimentRecurent&);
    friend ostream& operator<<(ostream&, const evenimentRecurent);
};

