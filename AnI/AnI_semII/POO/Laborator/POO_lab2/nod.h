#ifndef _NOD_H_
#define _NOD_H_
class nod
{
    int info;
    nod *next;
    public:
    nod();
    nod(int x, nod *n);
    void setInfo(int x);
    int getInfo();
    void setNext(nod *n);
    nod *getNext();
};
#endif // _NOD_H_
