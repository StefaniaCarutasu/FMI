#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;
map<int, vector<pair<int, int>>> listaAdiacentaPonderi;
vector<pair<int, pair<int, int>>> vectorPonderi;
vector<pair<int, pair<int, int>>> vectorArbore;
vector<int> vizitati;
const int infinit = INT_MAX;

//Citim graful si formam lista de adiacenta si vectorul de ponderi
void citireGraf()
{
	ifstream f("graf.in");
	int plecare, sosire, pondere;
	while (f >> plecare >> sosire >> pondere)
	{
		listaAdiacentaPonderi[plecare].push_back(make_pair(sosire, pondere));
		listaAdiacentaPonderi[sosire].push_back(make_pair(plecare, pondere));
		vectorPonderi.push_back(make_pair(pondere, make_pair(plecare, sosire)));
	}
	int n = listaAdiacentaPonderi.size();
	
}

void afisareListaAdiacentaPonderi(map<int, vector<pair<int, int>>> l)
{
	for (int i = 1; i < l.size(); i++)
	{
		cout << i << ": ";
		for (int j = 0; j < l[i].size(); j++)
		{
			cout << "(" << l[i][j].first << ", " << l[i][j].second << ") ";
		}
		cout << '\n';
	}
}

void initializareVizitati()
{
	for (int i = 0; i <= listaAdiacentaPonderi.size(); i++)
		vizitati.push_back(0);
}

void Prim(vector<pair<int, pair<int, int>>> vp, vector<pair<int, pair<int, int>>> va)
{
	vector<pair<int, pair<int, int>>> coada;
	for (auto i : vp)
	{
		if (i.second.first == 1 || i.second.second == 1)
			coada.push_back(i);
	}
	vizitati[1] = 1;
	while (coada.size() < vp.size())
	{
		pair<int, pair<int, int>> p = make_pair(infinit,make_pair(0,0));
		for (auto i : coada)
			if (i.first < p.first)
				p = i;
		va.push_back(p);
		int j;
		if (vizitati[p.second.first] == 0)
		{
			vizitati[p.second.first] = 1;
			j = p.second.first;
		}
		else
		{
			vizitati[p.second.second] = 1;
			j = p.second.second;
		}
		for (auto i : coada)
			if (i == p)
				i.first = infinit;
		for (auto i : vp)
		{
			if (i.second.first == j || i.second.second == j)
				coada.push_back(i);
		}
	}
}

int main()
{
	citireGraf();
	initializareVizitati();
	//afisareListaAdiacentaPonderi(listaAdiacentaPonderi);
	return 0;
}