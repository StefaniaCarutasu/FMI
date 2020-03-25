#include "lista.h"
#include "nod.h"
#include<climits>
#include<set>
using namespace std;
lista::lista()
{
        size=0;
        start=NULL;
        end=NULL;
}

lista::~lista()
{
    nod *p = start;
        while(p != NULL)
            {

            nod *q = p->getNext();
            delete p;
            p = q;
            }
}

lista::lista(int x, int y)
{
    size=0;
        start=NULL;
        end=NULL;
        for(int i=0;i<x;i++)
            inserare(y);
}
void lista::inserare(int x)
{
    if(start==NULL)
        {
            start=new nod(x,NULL);
            end=start;
            size=1;

        }
        else
        {
            end->setNext(new nod(x,NULL));
            size++;
            end=end->getNext();
        }
}
void lista::insertAt(unsigned int i, int x)
    {
        if(i<=0)
        {
            nod *p=new nod(x,start);
            start=p;
            size++;
        }
        else if(i>size)
        {
            inserare(x);
        }
        else
        {
            nod *q=start;
            unsigned int j=0;
            while(j<i)
            {
                q=q->getNext();

            }
            nod *p=new nod (x,q->getNext());
            q->setNext(p);
            size++;
        }
    }
int lista::get(unsigned int i)
     {
        if( i >= 0 && i < size)
            {
            nod *p = start;
            for(unsigned int j = 0; j < i; j++)
                p = p->getNext();
            return p->getInfo();
            }
        else return INT_MAX;
    }
int lista::length()
    {
        return size;
    }

void lista::remove(unsigned int i)
    {
        if(i == 0)
        {
            nod *p = start;
            start = start->getNext();
            delete p;
        }
        else
        {
            if(i < size)
            {
                nod *p = start;
                for(unsigned int j = 0; j < i-1; j++)
                    p = p->getNext();
                nod *q = p->getNext();
                p->setNext(q->getNext());
                delete q;
            }
        }
    }
    lista::lista reverse()
    {
        Lista l;
        nod *p = start;
        for(unsigned int i = 0; i < size; i++)
            {
            l.insertAt(p->getInfo(), 0);
            p = p->getNext();
            }
        return l;
    }
    void lista::removeFirst()
    {
        remove(0);
    }
    void lista::removeLast()
    {
        remove(size-1);
    }
    bool lista::hasDuplicates()
    {
        set<int> v;
        nod *p = start;
        while(p != NULL)
        {
            v.insert(p->getInfo());
            p = p->getNext();
        }
        if(v.size() == size)
            return false;
        return true;
        }
    bool lista::has(int x)
    {
        nod *p = start;
        while(p != NULL)
            {
            if(x == p->getInfo())
                return true;
            p = p->getNext();
            }
        return false;
    }
    bool lista::isEmpty()
    {

        if(size == 0)
            return true;
        return false;
    }
