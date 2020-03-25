#ifndef LISTA_H
#define LISTA_H
#include "nod.h"
class lista
{   nod *start, *end;
    unsigned int size;
    public:
        lista();
        virtual ~lista();
        lista(int, int); //copiere
        void inserare(int);
        void insertAt(int, int);
        int get(int i);
        int lengh();
        void remove(int i);
        lista reverse();
        void removeFirst();
        void removeLast();
        bool hadDuplicates();
        bool has(int);
        bool isEmpty();


};

#endif // LISTA_H
