#include <iostream>
#include<climits>
#include<set>
using namespace std;

//1-3
class nod
{
    int info;
    nod *next;

 public:
    nod()
    {
        info=0;
        next=NULL;

    }

    nod(int x, nod *n)
    {
        info=x;
        next=n;
    }

    void setInfo(int x)
    {
        info=x;
    }
    int getInfo()
    {
        return info;
    }
    void setNext(nod *n)
    {
        next=n;
    }
    nod *getNext()
    {
        return next;
    }


};

//4
class Lista
{
    nod *start;
    nod *end;
    unsigned int size;
//5
public:
    Lista()
    {
        size=0;
        start=NULL;
        end=NULL;

    }

    Lista(int x, int y)
    {
        size=0;
        start=NULL;
        end=NULL;
        for(int i=0;i<x;i++)
            inserare(y);
    }

   //6

    void inserare(int x)
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
    void insertAt(int i, int x)
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
    int get(int i)
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
    int lengh()
    {
        return size;
    }
    void remove(int i)
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
    //7
    void f(Lista l, int x)
    {
        for(int i=0; i<l.lengh(); i++)
            cout<<l.get(i)<<" ";
        l.inserare(x);
    }
    //9
    ~Lista()
    {
        nod*p=start;
        while(p!=NULL)
        {
            nod*q=p->getNext();
            delete p;
            p=q;
        }
    }
    //10
    Lista reverse()
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
    //11
    void removeFirst()
    {
        remove(0);
    }
    void removeLast()
    {
        remove(size-1);
    }
    //12
    bool hasDuplicates()
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
    //13
    bool has(int x)
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
    bool isEmpty()
    {
        if(size==0)
            return true;
        else return false;
    }

};
int main()
{

}
