#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
int nrNoduri;
vector<int> vizitati;
map<int, vector<int>> listaAdiacenta;
void afisareListaAdiacenta(map <int, vector <int> > L)
{

	for (unsigned int i = 1; i <= L.size(); i++)
	{
		cout << i << ": ";
		for (unsigned int j = 0; j < L[i].size(); j++)
			cout << L[i][j] << " ";
		cout << '\n';
	}
}
map<int, vector<int>> citireListaAdiacenta(int &n)
{
	map<int, vector<int>> listaAdiacenta;
	ifstream f("graf.in");
	f >> n;
	int x, y;
	while (f >> x >> y)
	{
		listaAdiacenta[x].push_back(y);
		listaAdiacenta[y].push_back(x);
	}
	f.close();
	return listaAdiacenta;
}


void esteConex(map<int, vector<int>> listaAdiacenta, int n)
{
	vector<int> vizitati(n + 1, 0), coada;
	int nod = 1;
	vizitati[nod] = 1;
	coada.push_back(nod);
	bool ok = true;
	while (!coada.empty())
	{
		nod = *coada.begin();
		coada.erase(coada.begin());
		for (auto i : listaAdiacenta[nod])
		{
			if (vizitati[i] == 0)
			{
				vizitati[i] = 1;
				coada.push_back(i);
			}
		}

	}
	for (int i = 1; i <= n; i++)
		if (vizitati[i] == 0)
		{
			cout << "Nu este conex";
			ok = false;
			break;
		}
	if (ok)
		cout << "Este conex";		
}

void dfs(int nod)
{
	vizitati[nod] = 1;
	cout << nod << " ";
	for (auto i : listaAdiacenta[nod])
		if (vizitati[i] == 0)
			dfs(i);
}

int main()
{
	listaAdiacenta = citireListaAdiacenta(nrNoduri);
	afisareListaAdiacenta(listaAdiacenta);
	//esteConex(listaAdiacenta, nrNoduri);
	for (int i = 0; i <= nrNoduri; i++)
		vizitati.push_back(0);
	dfs(1);
	return 0;
}
