#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;
map<int, vector<int> > listaAdiacenta;
vector<pair<int, pair<int, int>>> vectorPonderi;
vector<vector<int>> matriceAdiacenta;
const int infinit = INT_MAX;

//Citim graful si formam lista de adiacenta si vectorul de ponderi
void citireGraf()
{
	int n;
	ifstream f("graf.in");
	f >> n;
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
			matriceAdiacenta[i].push_back(0);
	}
	int plecare, sosire, pondere;
	while (f >> plecare >> sosire >> pondere)
	{
		listaAdiacenta[plecare].push_back(sosire);
		listaAdiacenta[sosire].push_back(plecare);
		vectorPonderi.push_back(make_pair(pondere, make_pair(plecare, sosire)));
		matriceAdiacenta[plecare][sosire] = pondere;
		matriceAdiacenta[sosire][plecare] = pondere;
	}

}

void afisareListaAdiacentaPonderi(map<int, vector<int> > l)
{
	for (int i = 1; i < l.size(); i++)
	{
		cout << i << ": ";
		for (int j = 0; j < l[i].size(); j++)
		{
			cout << l[i][j] << " ";
		}
		cout << '\n';
	}
}

void dijkstra(map<int, vector<int> > la, int src)
{
	int n = listaAdiacenta.size();
	vector<int> dist(n, infinit), vizitati(n, 0);
	dist[src] = 0;
	for (int i = 1; i < n; i++)
	{
		int min = infinit, min_index;
		for (int v = 1; v < n; v++)
		{
			if (vizitati[v] == 0 && dist[v] <= min)
			{
				min = dist[v];
				min_index = v;
			}
		}
		vizitati[min_index] = 1;
		for (int v = 1; v < n; v++)
		{
			if (!vizitati[min_index] && matriceAdiacenta[min_index][v] && dist[min_index] != infinit && dist[min_index] + matriceAdiacenta[min_index][v] < dist[v])
				dist[v] = dist[min_index] + matriceAdiacenta[min_index][v];
		}
	}

	cout << "Distanta pana la noduri:\n";
	for (int i = 1; i < n; i++)
	{
		cout << src << "->" << i << " " << dist[i];
	}
}


int main()
{
	citireGraf();
	//afisareListaAdiacentaPonderi(listaAdiacentaPonderi);
	dijkstra(listaAdiacenta, 1);
	return 0;
}