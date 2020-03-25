#include <iostream>
#include <map>
#include <string>
#include <set>
#include <fstream>
using namespace std;

class lambdaNFA
{
	set<int> Q, F;
	set<char> Sigma;
	set<int> q0;
	map<pair<int, char>, set<int> > delta;

public:
	lambdaNFA() { this->q0.insert(0); }
	lambdaNFA(set<int> Q, set<char> Sigma, map<pair<int, char>, set<int> > delta, set<int> q0, set<int> F)
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

	friend istream& operator >> (istream&, lambdaNFA&);

	set<int> lambdaInchidere(int);
	bool isFinalState(set<int>);
	set<int> deltaStar(set<int>, string);
};

set<int> lambdaNFA::lambdaInchidere(int stare)
{
	set<int> lambdaTranzitii;
	lambdaTranzitii.insert(stare);
	for (set<int>::iterator i = lambdaTranzitii.begin(); i != lambdaTranzitii.end(); i++)
	{
		for (set<int>::iterator j = delta[{*i, '#'}].begin(); j != delta[{*i, '#'}].end(); j++)
			lambdaTranzitii.insert(*j);
	}
	return lambdaTranzitii;
}

bool lambdaNFA::isFinalState(set<int> stari)
{
	for (set<int>::iterator i = stari.begin(); i != stari.end(); i++)
		if (F.find(*i) != F.end())
			return true;
	return false;
}

set<int> lambdaNFA::deltaStar(set<int> S, string v)
{
	int l = v.length();
	int contor = 0;
	set<int> localFinalStates, aux;
	localFinalStates.insert(*S.begin());
	while (l)
	{
		set<int> lTranzitii;
		for (set<int>::iterator i = localFinalStates.begin(); i != localFinalStates.end(); i++)
		{
			lTranzitii = lambdaInchidere(*i);
			for (set<int>::iterator j = lTranzitii.begin(); j != lTranzitii.end(); j++)
				aux.insert(*j);
		}
		localFinalStates.clear();
		for (set<int>::iterator i = aux.begin(); i != aux.end(); i++)
		{
			for (set<int>::iterator j = delta[{*i, v[contor]}].begin(); j != delta[{*i, v[contor]}].end(); j++)
				localFinalStates.insert(*j);
		}
		aux.clear();
		l--; contor++;
	}
	set<int> lTranzitii;
	for (set<int>::iterator i = localFinalStates.begin(); i != localFinalStates.end(); i++)
	{
		lTranzitii = lambdaInchidere(*i);
		for (set<int>::iterator j = lTranzitii.begin(); j != lTranzitii.end(); j++)
			aux.insert(*j);
	}
	return aux;
}

istream& operator >> (istream& f, lambdaNFA& M)
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
	f >> noOfTransitions;
	while (noOfTransitions)
	{
		int s, nr_trans;
		char ch;
		f >> s >> ch >> nr_trans;
		for (int i = 0; i < nr_trans; ++i)
		{
			int x;
			f >> x;
			M.delta[{s, ch}].insert(x);
		}
		noOfTransitions -= nr_trans;
	}
	int x;
	f >> x;
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
	lambdaNFA M;

	ifstream fin("lnfa.txt");
	fin >> M;
	fin.close();

	set<int> lastState = M.deltaStar(M.getInitialState(), "babbbaa"); 

	if (M.isFinalState(lastState))
	{
		cout << "Cuvant acceptat";   //accepta ababbbb
	}
	else
	{
		cout << "Cuvant respins";  //respinge babbbaa
	}

	return 0;
}
