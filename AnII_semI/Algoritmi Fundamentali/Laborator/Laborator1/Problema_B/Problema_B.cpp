#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
ifstream f("graf.in");
ofstream g("graf.out");

//Problema B
//1
void citireRetea(map<int, vector <int> > listaAdiacenta, vector<int> puncteControl)
{
	int n, m, x, y;
	f >> n >> m;
	for (int i = 0; i < m; i++)
	{
		f >> x >> y;
		listaAdiacenta[x].push_back(y);
		listaAdiacenta[y].push_back(x);
	}
	while (f >> x)
	{
		puncteControl.push_back(x);
	}
	f.close();
}

void lantMinim(map<int, vector <int> > listaAdiacenta, vector<int> puncteControl)
{
	int nod;
	cout << "Introduceti nodul";
	cin >> nod;
	vector<int> vizitati(listaAdiacenta.size() + 1, 0), coada, drum;
	vizitati[nod] = 1;
	coada.push_back(nod);
	drum.push_back(nod);
	bool ok = true;
	while (!coada.empty() && ok)
	{
		coada.erase(coada.begin());
		for (auto i : listaAdiacenta[nod])
		{
			if (vizitati[i] == 0)
			{
				vizitati[i] = 1;
				coada.push_back(i);
				drum.push_back(i);
			}
			vector<int> :: iterator it = find(puncteControl.begin(), puncteControl.end(), i);
			if (it != puncteControl.end())
			{
				ok = false;
				break;
			}
		}

	}
	for (auto i : drum)
	{
		g << i << " ";
	}
	g.close();

}

int main()
{
	return 0;
}