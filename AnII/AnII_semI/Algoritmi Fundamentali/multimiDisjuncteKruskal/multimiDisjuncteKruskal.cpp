#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>
#include<string>

using namespace std;
vector<vector<int>> muchii;
vector<int> tata, h;

void citire()
{
    ifstream f("multimi.in.txt");
    int x, y, z;
    while (f >> x >> y >> z)
    {
        vector<int> v;
        v.push_back(x), v.push_back(y), v.push_back(z);
        muchii.push_back(v);
    }
}

void Initializare(int u)
{
    tata[u] = h[u] = 0;
}

int Reprez(int u)
{
    while (tata[u]!= 0)
    {
        u = tata[u];
    }
    return u;
}

void Reuneste(int u, int v)
{
    int ru = Reprez(u), rv = Reprez(v);

    if (h[ru] > h[rv])
        tata[rv] = ru;
    else
    {
        tata[ru] = rv;
        if (h[ru] == h[rv])
        {
            h[rv] = h[rv] + 1;
        }
    }
}

bool comparaPonderi(vector<int> v1, vector<int> v2)
{
    return v1[2] > v2[2];
}

void Kruskal()
{
    vector<vector<int>> subarbore;
    //Sortam muchiile in oridinea ponderilor
    sort(muchii.begin(), muchii.end(), comparaPonderi);
    for (int v = 1; v <= muchii.size(); v++)
        Initializare(v);
    int nrmsel = 0;
    for (auto uv : muchii)
    {
        if (Reprez(uv[0]) != Reprez(uv[1])) //uv[0] e varful u si uv[1] este varful v
        {
            subarbore.push_back(uv); //E(T) = E(T) reunit cu uv
            Reuneste(uv[0], uv[1]);
            nrmsel++;
            if (nrmsel == muchii.size() - 1)
                break;
        }
    }
}

int main()
{
    return 0;
}