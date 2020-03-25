#include<iostream>
#include "nod.h"
using namespace std;
nod::nod()
{
    info=0;
    next=NULL;
}
nod::nod(int x, nod *n)
    {
        info=x;
        next=n;
    }

    void nod::setInfo(int x)
    {
        info=x;
    }
    int nod::getInfo()
    {
        return info;
    }
    void nod::setNext(nod *n)
    {
        next=n;
    }
    nod* nod::getNext()
    {
        return next;
    }
