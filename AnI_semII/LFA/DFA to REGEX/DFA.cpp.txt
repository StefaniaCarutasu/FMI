#include "DFA.h"
DFA::DFA(): q0(0) {}
DFA::DFA(set<int> Q, set<string> Sigma, map<pair<int, string>, int> delta, int q0, set<int> F) : Q(Q), Sigma(Sigma), delta(delta), q0(q0), F(F) {}
istream& operator >> (istream& f, DFA& M) 
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
		string ch;
		f >> ch;
		M.Sigma.insert(ch);
	}

	int noOfTransitions;
	f >> noOfTransitions;
	for (int i = 0; i < noOfTransitions; ++i) 
	{
		int s, d;
		string ch;
		f >> s >> ch >> d;
		M.delta[{s, ch}] = d;
	}

	f >> M.q0;

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

string DFA::dfaToRegex()
{
	string lambda = "£";
	string** matrix;  // creez o matrice care va retine drumul dintre oricare 2 stari din AFD
	//toate starile vor fi incrementate cu 1 pentru a putea lasa loc pentru o eventuala stare initiala auxiliara
	matrix = new string * [Q.size()+2];
	for (int i = 0; i < Q.size() + 2; i++)
		matrix[i] = new string[Q.size() + 2];
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < Q.size() + 2; j++)
			matrix[i][j] = "";

	int newInit = this->q0 + 1; //starea initiala auxiliara este starea initiala a DFA ului pana verificam daca exista tranzitii care intra in starea initiala
	//pas 1.1: verific daca exista tranzitii care intra in starea initiala
	for (auto& i : this->delta)
		if (i.second == this->q0) //exista o tranzitie
		{
			newInit = 0;  // creez o noua stare initiala
			matrix[newInit][this->q0 + 1] = lambda;  //ii adaug lambda tranzitie
			break;
		}

	int newFinal = *this->F.begin() + 1; //starea finala este starea finala a DFA ului pana verificam daca vreuna din conditii este indeplinita
	//pas 1.2: verific daca exista mai multe stari finale
	if (this->F.size() > 1)
	{
		newFinal = this->Q.size() + 1;
		//daca exista fac o noua stare finala si adaug cate o lambda tranzitie de la noua stare adaugata la toate starile finale ale automatului
		for (auto& i : this->F)
			matrix[i + 1][newFinal] = lambda;
	}
	else
	{
		//pas 1.3: verific daca exista tranzitie ce porneste din starea finala
		for (auto& i : this->delta)
			if (i.first.first == *F.begin())  //daca gasesc tranzitie
			{
				newFinal = Q.size() + 1;  //imi fac o noua stare finala
				matrix[*F.begin() + 1][newFinal] = lambda;  // adaug lambda tranzitia de la noua stare finala la vechea stare finala

			}
	}
	//daca nu se intampla niciuna dintre cele 2 conditii de la 1.2 si 1.3 atunci automatul are o singura stare finala
	//si din ea nu mai porneste nicio tranzitie; starea finala ramane starea finala a automatului

	//pas2: formez AFE
	for (auto& i : delta)
		if (matrix[i.first.first + 1][i.second + 1] == "")
			matrix[i.first.first + 1][i.second + 1] = i.first.second;
		else matrix[i.first.first + 1][i.second + 1] = "( " + matrix[i.first.first + 1][i.second + 1] + "+" + i.first.second + " )";
	
	//pas3: formez o multime noua doar cu acele stari ale automatului care nu sunt initiale sau finale
	set<int> stariAuxiliare;
	for (auto& i : Q)
		if ((i + 1) != newInit && (i + 1) != newFinal)
			stariAuxiliare.insert(i + 1);
	int noOfStates = stariAuxiliare.size() + 2; //nr stari AFE
	//pas4: pe rand voi elimina fiecare stare intermediara a automatului, construind expresia regulata
	set <int> stariCurente;		//un set cu starile automatului dupa fiecare eliminare				
	for (int i = 0; i < noOfStates; i++)
		stariCurente.insert(i);
	for(auto& st: stariAuxiliare)
	{
		stariCurente.erase(st);
		set<int> in;	//multimea starilor de la care exista o tranzitie spre starea curenta
		set<int> out;	//multimea starilor la care ajunge o tranzitie care pleaca din starea curenta
		for (auto& it : stariAuxiliare)
		{
			if (matrix[it][st] != "")
				in.insert(it);
			if (matrix[st][it] != "")
				out.insert(it);
		}
		//verific daca exista bucla, adica vreo tranzitie de la la starea curenta la ea insasi
		string bucla = "";
		if (matrix[st][st] != "")
			if (matrix[st][st].length() == 1)
				bucla = matrix[st][st] + "*";
			else bucla = "( " + matrix[st][st] + " )" + "*";
		//prin eliminarea unei stari trebuie refacute tranzitiile dintre starile care au tranzitii ce intra in starea curenta si starile care au tranzitii care pleaca din starea curenta
		//altfel spus trebuie refacute tranzitiile dintre starile din in si cele din out
		for(auto& i: in)
			for (auto& o : out)
				matrix[i][o] = matrix[i][o] + "( " + matrix[i][st] + " )( " + bucla + " )( " + matrix[st][o] + " )";
	}
	return matrix[newInit][newFinal];

}
