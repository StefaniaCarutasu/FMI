#ifndef NOD_H
#define NOD_H

class lista;
class nod
{   int info;
    nod *next;
    public:
        nod();
        nod(int, nod);
        virtual ~nod();
        void setinfo(int);
        int getInfo();
        void setNext(nod);
        nod *getNext();
    friend class lista;
};

#endif // NOD_H
