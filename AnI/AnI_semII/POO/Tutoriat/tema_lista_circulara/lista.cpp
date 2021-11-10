#include "lista.h"
#include "node.h"
#include<iostream>
using namespace std;

lista::lista() : length(0), start(NULL), end(NULL) {} //constructor fara parametrii

lista::lista(int v[], int n)  //constructor cu prametrii
{
    length = 0; start = NULL; end = NULL;
    for (int i = 0; i < n; i++)
    {
        inserareFinal(v[i]);
    }
}

lista::~lista() //destructor
{ 
    this->length = 0;
    node* p = start;
    while (p) {
        node* q = p->next;
        delete p;
        p = q;
    }
}

void lista::inserareInceput(int x)
{
    node* aux = new node;
    aux->info = x;
    aux->next = start;
    aux->before = NULL;
    if (start != NULL)
        start->before = aux;
    start = aux;
    end->next = start;
    length++;
}

void lista::inserareFinal(int x)
{
    node* aux = new node;
    aux->info = x;
    aux->next = NULL;
    aux->before = NULL;
    if (start == NULL)
    {
        start = aux; end = aux;
    }
    else
    {
        end->next = aux;
        aux->before = end;
        aux->next = start;
        end = aux;
    }
    length++;

}

void lista::inserarePoz(int x, int poz)
{
    node* aux = new node;
    aux->info = x;
    aux->next = NULL;
    aux->before = NULL;
    if (length == 0)
    {
        start = aux;
    }
    else
    {
        int i = 0;
        node* p = start;
        while (i != poz)
        {
            p = p->next; i++;
        }
        aux->next = p;
        aux->before = p->before;
        p->before = aux;

    }
    length++;
}

void lista::stergerePoz(int poz)
{
    int i = 0;
    node* aux = start;
    while (i != poz)
    {
        aux = aux->next;
        i++;
    }
    aux->before->next = aux->next;
    aux->next->before = aux->before;
    delete aux;
    length--;
}

int lista::cautare(int x)
{
    node* aux = start;
    bool gasit = false;
    int i = 0;
    while (i < length && gasit == false)
    {
        if (aux->info == x)
            return i;
        else
        {
            aux = aux->next;
            i++;
        }

    }
    if (gasit == false)
        cout << "Nu a fost gasit in lista";
}

int lista::Suma()
{
    node* aux = start; int suma = 0, i = 0;
    while (i < length)
    {
        suma += aux->info;
        aux = aux->next;
    }
    return suma;
}

int lista::nrElem()
{
    return this->length;
}

int lista::detMax()
{
    node* aux = start->next; int max = start->info;
    for (int i = 1; i < length; i++)
    {
        if (aux->info > max)
            max = aux->info;
        aux = aux->next;
    }
    return max;
}

int lista::detMin()
{
    node* aux = start->next; int min = start->info;
    for (int i = 1; i < length; i++)
    {
        if (aux->info < min)
            min = aux->info;
        aux = aux->next;
    }
    return min;
}
