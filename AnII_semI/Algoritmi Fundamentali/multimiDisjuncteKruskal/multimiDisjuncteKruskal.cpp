#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>
#include<string>

using namespace std;
//map<int, vector<int>> multimi;
vector<vector<int>> muchii;
vector<int> tata, h;

/*void citireMultimi()
{
    ifstream f("multimi.in.txt");
    int nrMultimi, j = 0;
    string nr, str = "";
    getline(f, nr);
    nrMultimi = stoi(nr);

    while (std::getline(f, str))
    {
        int i = 0;
        string s = "";
        int n;
        while (i < str.length())
        {
            if (str[i] != ' ')
            {
                s += str[i];
                i++;
            }
            else 
            {
                n = stoi(s);
                multimi[j].push_back(n);
                i++;
                s = "";
                r.push_back(0);
            }
            if (i == str.length())
            {
                n = stoi(s);
                multimi[j].push_back(n);
                i++;
                s = "";
                r.push_back(0);
            }
        }
        j++;
    }

}*/

bool comparaPonderi(vector<int> v1, vector<int> v2)
{
    return v1[2] > v2[2];
}

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
    //Sortam muchiile in oridinea ponderilor
    sort(muchii.begin(), muchii.end(), comparaPonderi);

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

void Kruskal()
{
    vector<vector<int>> coada;
    coada.push_back(muchii[0]);
}

int main()
{
    /*citireMultimi();
    int contor = 1;
    for (contor = 0; contor < multimi.size(); contor++)
    {
        cout << "Multimea " << contor + 1 << ": ";
        for (auto j : multimi[contor])
        {
            cout << j << " ";
        }
        cout << '\n';
    }*/

    return 0;
}