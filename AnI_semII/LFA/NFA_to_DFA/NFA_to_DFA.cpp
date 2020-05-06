#include<iostream>
#include<fstream>
#include<map>
#include<set>
#include<vector>
#include<string>
using namespace std;
ifstream f("nfa.txt");

class DFA
{
	vector<string> QDFA, FDFA;
	set<char> SigmaDFA;
	set<int> q0DFA;
	map<pair<string, char>, string> deltaDFA;
public:
	DFA() { this->q0DFA.insert(0); }
	DFA(vector<string> Q, set<char> Sigma, map<pair<string, char>, string> delta, set<int> q0, vector<string> F)
	{
		this->QDFA = Q;
		this->SigmaDFA = Sigma;
		this->deltaDFA = delta;
		this->q0DFA = q0;
		this->FDFA = F;
	}
	map<pair<string, char>, string> getDelta() { return this->deltaDFA; }
	void setQ(vector<string> q) { this->QDFA = q; }
	void setF(vector<string> f) { this->FDFA = f; }
	void setSigma(set<char> s) { this->SigmaDFA = s; }
	void setInitialState(set<int> q) { this->q0DFA = q; }
	set<int> getQ0() { return this->q0DFA; }
	vector<string> getQDFA() { return this->QDFA; }
	vector<string> getFDFA() { return this->FDFA; }
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
	DFA nfaToDFA();
};


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

DFA NFA::nfaToDFA()
{
	DFA aux;
	aux.setInitialState(this->getInitialState());
	vector<string> coada, QLocal;
	for(auto& i: this->getQ())
		coada.push_back(to_string(i)); //adaug in coada prima stare a NFA-ului
	map<pair<string, char>, set<int>> delta_local;

	for (auto& i : this->getDelta())
	{
		delta_local[{to_string(i.first.first),i.first.second}] =i.second;  //am facut un delta local si am facut starile string pt a lucra mai usor
	}

	while (coada.size())  //adaug in coada toate starile pe rand si multimile de stari din care se ajunge cu fiecare litera
	{
		for (auto& lit : this->getSigma()) //fiecare litera din alfabet
		{
			if (coada[0].size() == 1) //daca e stare initiala din nfa
			{
				for (auto& i : delta_local)
				{
					if (i.first.first == coada[0] && to_string(i.first.second) == to_string(lit))
					{
						string st = ""; //daca ajunge in mai multe stari atunci fac un string cu toate
						if (i.second.size() > 1)
						{
							for (auto& it : i.second)
								st += to_string(it) + ","; //o fac sa fie o stare de sine statatoare
						}
						else st = to_string(*i.second.begin());
						int ok = 0;
						for (auto& j : coada) //verific daca se afla deja in coada
							if (j == st)
								ok = 1;
						if (ok == 0)
							coada.push_back(st); //adaugam in coada daca nu era deja
						
					}
				}
			}
		
			else  //daca e stare formata dintr-o multime de stari lungimea stringului va fi sigur >1
			{
				set<int> multime;
				int l = 0;
				while(l<coada[0].size())
				{
					string stare = "";
					while (coada[0][l] != ',')  //tratam separat fiecare stare din multime si facem reuniunea multimilor de stari in care ajung
					{
						stare += coada[0][l];
						l++;
					}
					l++;
					//repet procesul de la stare simpla dar adaug la coada de abia la final
					for (auto& i : delta_local)
					{
						if (i.first.first == coada[0] && to_string(i.first.second) == to_string(lit))
							for (auto& a : i.second)
								multime.insert(a); //adaug la set toate starile in care se ajunge cu litera curenta din fiecare stare din multime
					}
					
				}
				delta_local[{coada[0], lit}] = multime;
				string stare = "";
				if (multime.size() > 1)
					for (auto& it : multime)
						stare += to_string(it) + ","; //o fac sa fie o stare de sine statatoare
				else
					for (auto& it : multime)
						stare += to_string(it);
				bool ok = 0;
				for (auto& j : coada)
					if (j == stare)
						ok = 1;
				if (ok == 0)
				{
					coada.push_back(stare); //adaugam in coada daca nu era deja
				}
			}		
		}

		QLocal.push_back(*coada.begin());//inainte sa o sterg din coada o adaug la strile locale
		coada.erase(coada.begin());
	}
	//dupa ce am creat delta pt dfa acum cream F
	vector<string> finale;
	for (auto& i : QLocal)
	{
		for (auto& j : this->getF()) //verificam daca starea are in alcatuirea sa o stare finala a NFA-ului
			if (i.find(to_string(j)))
			{
				finale.push_back(i);  //daca are atunci este stare finala si in DFA si o adaugam la starile finale 
				break;
			}
	}
	aux.setF(finale); //starile finale
	aux.setQ(QLocal); //toate starile
	for (auto& i : delta_local)
	{
		string st = "";
		for (auto& j : i.second)
			st += to_string(j);
		aux.deltaDFA[i.first] = st;  // cream delta al DFA-ului 

	}
	aux.setSigma(this->getSigma());
	return aux;
}
int main()
{
	NFA M;
	f >> M;
	DFA D;
	D = M.nfaToDFA();
	cout << "Starea initiala este: ";
	for (auto& i : D.getQ0())
		cout << i << " ";
	cout << '\n';
	cout << "Starile sunt: ";
	for (auto& i : D.getQDFA())
		cout << i << "  ";
	cout << '\n';
	cout << "Automatul devine:\n";
	for (auto& i : D.getDelta())
	{
		cout << i.first.first << "+" << i.first.second << "->" << i.second<<'\n';  //afisez, pe rand, tranzitiile
	}
	return 0;
}