#include<iostream>
#include<map>
#include<set>
#include<vector>
#include<string>
using namespace std;
class DFA
{
	set<int> QDFA, FDFA;
	set<char> SigmaDFA;
	set<int> q0DFA;
	map<pair<int, char>, int> deltaDFA;
public:
	DFA() { this->q0DFA.insert(0); }
	DFA(set<int> Q, set<char> Sigma, map<pair<int, char>, int> delta, set<int> q0, set<int> F)
	{
		this->QDFA = Q;
		this->SigmaDFA = Sigma;
		this->deltaDFA = delta;
		this->q0DFA = q0;
		this->FDFA = F;
	}
	void setQ(set<int> q) { this->QDFA = q; }
	void setF(set<int> f) { this->FDFA = f; }
	void setSigma(set<char> s) { this->SigmaDFA = s; }
	void setInitialState(set<int> q) { this->q0DFA = q; }
	friend class NFA;
};
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

	DFA nfaToDFA(NFA M);
};
bool NFA::isFinalState(set<int> stari)
{
	for (set<int>::iterator it = stari.begin(); it != stari.end(); it++)
		if (F.find(*it) != F.end())
			return true;
	return false;
}


istream& operator >> (istream& in, NFA& M)
{
	int noOfStates;
	in >> noOfStates;
	for (int i = 0; i < noOfStates; ++i)
	{
		int q;
		in >> q;
		M.Q.insert(q);
	}

	int noOfLetters;
	in >> noOfLetters;
	for (int i = 0; i < noOfLetters; ++i)
	{
		char ch;
		in >> ch;
		M.Sigma.insert(ch);
	}

	int noOfTransitions;
	in >> noOfTransitions;
	while (noOfTransitions)
	{
		int s, nr_trans;
		char ch;
		in >> s >> ch >> nr_trans;
		for (int i = 0; i < nr_trans; ++i)
		{
			int x;
			in >> x;
			M.delta[{s, ch}].insert(x);
		}
		noOfTransitions -= nr_trans;
	}
	int x;
	in >> x;
	M.q0.insert(x);


	int noOfFinalStates;
	in >> noOfFinalStates;
	for (int i = 0; i < noOfFinalStates; ++i)
	{
		int q;
		in >> q;
		M.F.insert(q);
	}

	return in;
}
DFA NFA::nfaToDFA(NFA M)
{
	DFA aux;
	aux.setInitialState(M.getInitialState);
	set<string> coada;
	for (auto& st : M.getQ())
	{
		coada.insert(to_string(st));
		for (auto& lit : M.getSigma())
		{
			set<int> urmStare = M.getDelta()[{st, lit}];
			string st_comp = "";
			for (auto& i : urmStare)
			{
				st_comp = to_string(i) + ',';
			}
			coada.insert(st_comp);
		}
		
	}
}
int main()
{
	return 0;
}

