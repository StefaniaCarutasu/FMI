#include <iostream>
#include <map>
#include <string>
#include <set>
#include <fstream>
using namespace std;

class NFA
{
	set<int> Q, F;
	set<char> Sigma;
	set<int> q0;
	map<pair<int, char>, set<int> > delta;

public:
	NFA() { this->q0.insert(0); }
    NFA(set<int> Q, set<char> Sigma, map<pair<int, char>, set<int> > delta, set<int> q0, set<int> F)
	{
		this->Q = Q;
		this->Sigma = Sigma;
		this->delta = delta;
		this->q0 = q0;
		this->F = F;
	}

	set<int> getQ() const { return this->Q; }
	set<int> getF() const { return this->F; }
	set<char> getSigma() const { return this->Sigma; }
	set<int> getInitialState() const { return this->q0; }
	map<pair<int, char>, set <int> > getDelta() const { return this->delta; }

	friend istream& operator >> (istream&, NFA&);

	bool isFinalState(set<int>);
	set<int> deltaStar(set<int>, string);
};

bool NFA::isFinalState(set<int> stari)
{
	for (set<int>::iterator it = stari.begin(); it != stari.end(); it++)
		if (F.find(*it) != F.end())
			return true;
	return false;
}

set<int> NFA::deltaStar(set<int> S, string w)
{
	int l = w.length(), contor=0;
	set<int> localFinalStates, aux;
	for (set<int>::iterator i = delta[{*S.begin(), w[contor]}].begin(); i != delta[{*S.begin(), w[contor]}].end(); i++)
	{
		localFinalStates.insert(*i);
	}
	l--;
	if (l == 0)
		return localFinalStates;
	while (l)
	{
		for (set<int>::iterator i = localFinalStates.begin(); i != localFinalStates.end(); i++)
			for (set<int>:: iterator j =  delta[{*i, w[contor]}].begin(); j != delta[{*i, w[contor]}].end(); j++)
				aux.insert(*j);
		l--; contor++;
		localFinalStates.clear();
		for (int i : aux)
			localFinalStates.insert(i);
		aux.clear();
	}
	return localFinalStates;
}

istream& operator >> (istream& f, NFA& M)
{
	int noOfStates;
	f >> noOfStates;
	for (int i = 0; i < noOfStates; ++i)
	{
		int q;
		f >> q;
		M.Q.insert(q);
	}

	int noOfLetters;
	f >> noOfLetters;
	for (int i = 0; i < noOfLetters; ++i)
	{
		char ch;
		f >> ch;
		M.Sigma.insert(ch);
	}

	int noOfTransitions;
	f>>noOfTransitions;
	while (noOfTransitions)
	{
		int s, nr_trans;
		char ch;
		f>>s>>ch>>nr_trans;
		for (int i = 0; i < nr_trans; ++i)
		{
			int x;
			f>>x;
			M.delta[{s, ch}].insert(x);
		}
		noOfTransitions -= nr_trans;
	}
    int x;
	f>>x;
	M.q0.insert(x);


	int noOfFinalStates;
	f >> noOfFinalStates;
	for (int i = 0; i < noOfFinalStates; ++i)
	{
		int q;
		f >> q;
		M.F.insert(q);
	}

	return f;
}

int main()
{
	NFA M;

	ifstream fin("nfa.txt");
	fin >> M;
	fin.close();

	set<int> lastState = M.deltaStar(M.getInitialState(), "aba");

	if (M.isFinalState(lastState))
	{
		cout << "Cuvant acceptat";
	}
	else
	{
		cout << "Cuvant respins";
	}

	return 0;
}
