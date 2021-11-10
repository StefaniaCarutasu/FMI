#include <iostream>
#include <vector>
using namespace std;

vector<int> vectorFiboRec;

int fiboRec(int n)
{
    if (n <= 1)
    {
        return n;
    }
    return fiboRec(n - 1) + fiboRec(n - 2);
}

vector<int> fiboIt(int n)
{
    vector<int> vectorFiboIt = { 0, 1 };
    for (int i = 2; i <= n; i++)
    {
        int el = vectorFiboIt[i - 1] + vectorFiboIt[i - 2];
        vectorFiboIt.push_back(el);
    }
    return vectorFiboIt;
}

void fiboItOpt(int n)
{
    int a = 0, b = 1, c, i = 2;
    cout << a << " " << b << " ";
    while (i <= n)
    {
        c = a + b;
        cout << c << " ";
        a = b;
        b = c;
        i++;
    }
}

int main()
{
    vector<int> it;
    int n;
    cout << "Introduceti n: ";
    cin >> n;
    it = fiboIt(n);
    cout << "Iterativ: ";
    for (auto i : it)
        cout << i << " ";
    cout << '\n';
   
    cout << "Recursiv: ";
    int i = 0;
    while (i <= n)
    {
        cout << fiboRec(i) << " ";
        i++;
    }
    cout << '\n';

    cout << "Iterativ optimizat: ";
    fiboItOpt(n);
   
}

