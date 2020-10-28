#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;
map<int, vector<pair<int, int>>> listaAdiacentaPonderi;
vector<pair<int, pair<int, int>>> vectorPonderi;
vector<pair<int, pair<int, int>>> vectorArbore;

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

//Sortam vectorul in ordinea crescatoare a ponderilor
bool comparaPonderi(pair<int, pair<int, int>> p1, pair<int, pair<int, int>> p2)
{
	return p1.first > p2.first;
}

bool comparaNod(pair<int, pair<int, int>> p1, pair<int, pair<int, int>> p2)
{
	return p1.second.first > p2.second.second;
}
//Daca avem n noduri in graful initial, arborele va avea n-1 muchii
//Pas1: scoatem buclele si muchiile paralele
//Pas2: Sortam muchiile dupa pondere
//Luam n-1 muchii
//Evitam ciclurile

void Kruskal()
{
	sort(vectorPonderi.begin(), vectorPonderi.end(), comparaPonderi);
	int n = listaAdiacentaPonderi.size();
	vector<int> vizitati(n, 0);
	int nrMuchii = 0, iterator = 0;
	while (nrMuchii < listaAdiacentaPonderi.size())
	{
		if (vizitati[vectorPonderi[iterator].second.first] == 0 || vizitati[vectorPonderi[iterator].second.second == 0])
		{
			vectorArbore.push_back(vectorPonderi[iterator]);
			nrMuchii++;
			vizitati[vectorPonderi[iterator].second.first] = 1;
			vizitati[vectorPonderi[iterator].second.second] = 1;
		}
		iterator++;
	}
}



int main()
{
	citireGraf();
	afisareListaAdiacentaPonderi(listaAdiacentaPonderi);
	return 0;
}
