#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>

using namespace std;
map<int, vector<pair<int, int>>> listaAdiacentaPonderi;
vector<pair<int, pair<int, int>>> vectorPonderi;
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



int main()
{
	citireGraf();
	initializareVizitati();
	//afisareListaAdiacentaPonderi(listaAdiacentaPonderi);
	return 0;
}