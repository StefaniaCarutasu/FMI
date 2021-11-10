#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main() {
    srand(time(NULL));
    int x = (rand()%20)+1; // returneaza un numar intre 0 si 20
    int y, v=3;
    cout<<"Ghiciti numarul, aveti 3 incercari ";
    cin>>y;
    do
    {
        if(x<y)
            {cout<<"Numarul introdus este prea mare, introduceti alt numar"<<endl;
             cin>>y;
             v--;
            }
        if(x>y)
            {cout<<"Numarul introdus este prea mic, introduceti alt numar"<<endl;
            cin>>y;
            v--;
            }
        if(x==y)
            cout<<"Felicitari, ati ghicit numarul!";
    } while(x!=y && v>0);
    if(v==0)
        cout<<"Numarul era "<<x;
        return 0;
}
