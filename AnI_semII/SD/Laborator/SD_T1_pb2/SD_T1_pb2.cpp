#include <iostream>
using namespace std;
struct coada {

    int info;

    coada* prev, * next;

} *first, * last;
void push_left(int x)
{
    coada* nod = new coada;
    nod->info = x;
    nod->prev = NULL;

    nod->prev = first;

    if (first != NULL)
        first->prev = nod;
    else
    {
        first = nod;
        last = nod;
    }
    first = nod;
    

}
void push_right(int x)
{
    coada* nod = new coada;
    nod->info = x;
    nod->next = NULL;
    nod->prev = NULL;
    if (last == NULL)
    {
        last = nod;
        first = nod;
    }
    else
    {
        last->next = nod;
        nod->prev = last;
        last = nod;
    }
}
void pop_left()
{
    if (first == NULL)
        return;
    else 
    {
        if (first->next == NULL)
        {
            cout << first->info << '\n';
            delete first;
        }
        else
        {
            coada* nod = new coada;
            nod = first;
            cout << nod->info << '\n';
            first = first->next;
            first->prev = NULL;
            delete nod;
        }
    }
}
void pop_right()
{   
    if (last == NULL)
        return;
    else
    {
        if (last->prev == NULL)
        {
            cout << last->info << '\n';
            delete last;
        }
        else
        {
            coada* nod = new coada;
            nod = last;
            cout << nod->info << '\n';
            last = last->prev;
            last->next = NULL;
            delete nod;
        }
    }
    
}
int main()
{
    first = last = NULL;
    push_left(1);
    push_right(2);
    pop_right();
    pop_left();
    push_right(3);
    return 0;

}