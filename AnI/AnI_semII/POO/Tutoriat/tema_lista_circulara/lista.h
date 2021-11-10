#pragma once
#include "node.h"
#include<fstream>
using namespace std;

class lista
{
    node* start;
    node* end;
    int length;
public:
    lista(); //facut
    lista(int[], int); //facut
    lista(const lista& l); //constructor de copiere candva sper!?!?!?!?
    ~lista(); //facut
    void inserareInceput(int);  //facut
    void inserarePoz(int, int);  //facut
    void inserareFinal(int);    //facut
    void stergerePoz(int);  //facut
    int cautare(int);   //facut
    int Suma(); //facut
    int nrElem();   //facut
    void inversare();
    int detMin();   //facut
    int detMax();   //facut
    friend ostream& operator << (ostream&, const lista&);
    friend istream& operator >> (istream&, const lista&);
    friend lista& operator + (const lista&, const lista&);
    friend lista& operator > (const lista&, const lista&);
    friend lista& operator < (const lista&, const lista&);
    lista& operator [] (const int&);
    lista& operator * (const int&);
    lista& operator = (const lista&);
    
};



