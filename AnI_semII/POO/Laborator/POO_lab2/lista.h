#ifndef _LISTA_H_
#define _LISTA_H_
class Lista
{
    nod *start;
    nod *end;
    unsigned int size;
public:
    Lista(); //constructor fara parametrii
    Lista(int x, int y); //constructor cu parametrii
    void inserare(int x);
    void insertAt(int i, int x);
    int get(int i);
    void remove(int i);
    void f(Lista l, int x);
     Lista reverse();
    ~Lista(); //destructor
    void removeFirst();
    void removeLast();
    bool hasDuplicates();
    bool has(int x);
    bool isEmpty();
    friend class nod;

};
#endif // _LISTA_H_
