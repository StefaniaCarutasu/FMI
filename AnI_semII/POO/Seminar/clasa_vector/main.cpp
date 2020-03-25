#include <iostream>

using namespace std;
class vect
{
    int *v;
    int size, start;
public:
    vect() //constructor fara parametri
    {
        v=new int[5];
        size=5;
        start=-1;

    }
    vect(int x) //constructor cu parametri
    {
        v=new int[x];
        size=x;
        start=-1;
        }

    vect( vect &w) //constructor de copiere
    {
        v=new int[w.size];
        size=w.size;
        start=w.start;
        for(int i=0; i<start; i++)
            v[i]=w.v[i];
    }
    ~vect() //destructor
    {
        delete[] v;
        size=0;
        start=-1;
    }
    void push_final(int x) //inserare la finalul vectorului
    {
        if(start==size)
        {
            int *w=new int[size+5];
            for(int i=0; i<size; i++)
                w[i]=v[i];
            size+=5;
            delete[]v;
            v=w;

        }
        v[++start]=x;
    }
    int pop_final() //returnare el final
    {
        if(start==-1)
            return -1;
        int x=v[start];
        start--;
        return x;
    }
    int returnare(int i)  //returneaza el de pe poz i
    {
        return v[i];
    }

    int return_nrEl(vect v)  //returneaza nr de el din vector
    {
        return v.start;
    }


};
int main()
{

    return 0;
}
