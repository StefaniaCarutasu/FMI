#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

//problema A

//1
vector < vector <int> > creareMatriceAdiacentaNeorientat()
{
    ifstream f("graf.in");
    int n, m, x, y;
    f >> n >> m;
    vector < vector <int> > matriceAdiacenta(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; i++)
    {
        f >> x >> y;
        matriceAdiacenta[x][y] = 1;
        matriceAdiacenta[y][x] = 1;
    }
    return matriceAdiacenta;
}

void afisareMatriceAdiacenta(vector < vector <int> > M)
{
    int n = M[0].size() - 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << M[i][j] << " ";
        cout << '\n';
    }
}

//2
map <int, vector <int> > creareListaAdiacentaNeorientat()
{
    ifstream f("graf.in");
    int n, m, x, y;
    f >> n >> m;
    map <int, vector <int> > listaAdiacenta;
    for (int i = 0; i < m; i++)
    {
        f >> x >> y;
        listaAdiacenta[x].push_back(y);
        listaAdiacenta[y].push_back(x);
    }
    return listaAdiacenta;
}

void afisareListaAdiacenta(map <int, vector <int> > L)
{

    for (int i = 1; i <= L.size(); i++)
    {
        cout << i << ": ";
        for (int j = 0; j < L[i].size(); j++)
            cout << L[i][j] << " ";
        cout << '\n';
    }
}

//3
vector < vector <int> > creareMatriceAdiacentaOrientat()
{
    ifstream f("graf.in");
    int n, m, x, y;
    f >> n >> m;
    vector < vector <int> > matriceAdiacenta(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; i++)
    {
        f >> x >> y;
        matriceAdiacenta[x][y] = 1;
    }
    return matriceAdiacenta;
}

map <int, vector <int> > creareListaAdiacentaOrientat()
{
    ifstream f("graf.in");
    int n, m, x, y;
    f >> n >> m;
    map <int, vector <int> > listaAdiacenta;
    for (int i = 0; i < m; i++)
    {
        f >> x >> y;
        listaAdiacenta[x].push_back(y);
    }
    return listaAdiacenta;
}

//4
vector < vector <int> > listToMatrix(map <int, vector <int> > L)
{
    vector < vector <int> > matriceAdiacenta(L.size() + 1, vector<int>(L.size() + 1, 0));
    for (int i = 1; i < L.size(); i++)
    {
        for (int j = 0; j < L[i].size(); j++)
        {
            matriceAdiacenta[i][L[i][j]] = 1;
        }
    }
    return matriceAdiacenta;
}

map <int, vector <int> > matrixToList(vector < vector <int> > M)
{
    map <int, vector <int> > listaAdiacenta;
    for (int i = 1; i < M.size(); i++)
    {
        for (int j = 0; j < M[i].size(); j++)
        {
            if (M[i][j] == 1)
                listaAdiacenta[i].push_back(j);
        }
    }
    return listaAdiacenta;

}


int main()
{
    afisareMatriceAdiacenta(creareMatriceAdiacentaNeorientat());
    cout << '\n';
    afisareListaAdiacenta(creareListaAdiacentaNeorientat());
    cout << '\n';
    afisareMatriceAdiacenta(creareMatriceAdiacentaOrientat());
    cout << '\n';
    afisareMatriceAdiacenta(listToMatrix(creareListaAdiacentaNeorientat()));
    cout << '\n';
    afisareListaAdiacenta(matrixToList(creareMatriceAdiacentaNeorientat()));
    return 0;
}
