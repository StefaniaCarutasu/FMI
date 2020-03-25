#include<iostream>
#include<climits>
#include<set>
#include"lista.h"
Lista::Lista()
{
        size=0;
        start=NULL;
        end=NULL;

}
Lista::Lista(int x, int y)
{
    size=0;
        start=NULL;
        end=NULL;
        for(int i=0;i<x;i++)
            inserare(y);
}
void Lista::inserare(int x)
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
void Lista::insertAt(int i, int x)
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
            int j=0;
            while(j<i)
            {
                q=q->getNext();

            }
            nod *p=new nod (x,q->getNext());
            q->setNext(p);
            size++;
        }
    }
int Lista::get(int i)
    {
        if(i<=size && i>=0)
        {
            nod*p=start;
            for(int j=0; j<i;j++)
                p=p->getNext();
            return p->getInfo();
        }
        else return INT_MAX;
    }
int Lista::lengh()
    {
        return size;
    }
void Lista::remove(int i)
    {
        nod *p=start;
        if(i==0)
        {
            start=start->getNext();
            delete p;
        }
        for(int j=0;j<i-1;j++)
        {
            p=p->getNext();
        }
        nod *q=p->getNext();
        p->setNext(q->getNext());
        delete q;
    }
void Lista::f(Lista l, int x)
    {
        for(int i=0; i<l.lengh(); i++)
            cout<<l.get(i)<<" ";
        l.inserare(x);
    }
Lista::~Lista()
    {
        nod*p=start;
        while(p!=NULL)
        {
            nod*q=p->getNext();
            delete p;
            p=q;
        }
    }
    Lista::reverse()
    {
        Lista l;
        nod*p=start;
        for(unsigned int i=0; i<size; i++)
        {
            l.insertAt(p->getInfo(),0);
            p=p->getNext();
        }
        return l;
    }
    void Lista::removeFirst()
    {
        remove(0);
    }
    void Lista::removeLast()
    {
        remove(size-1);
    }
    bool Lista::hasDuplicates()
    {
        set<int>v;
        nod*p=start;
        while(p!=NULL)
        {
            v.insert(p->getInfo());
            p=p->getNext();
        }
        if(v.size()==size)
            return false;
        else return true;
    }
    bool Lista::has(int x)
    {
        nod*p=start;
        while(p->getNext()!=NULL)
        {
            if(p->getInfo()==x)
            return true;
            p=p->getNext();
        }
        return false;

    }
    bool Lista::isEmpty()
    {
        if(size==0)
            return true;
        else return false;
    }

