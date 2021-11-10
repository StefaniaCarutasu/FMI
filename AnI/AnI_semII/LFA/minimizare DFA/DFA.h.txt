#pragma once
#include<iostream>
#include<fstream>
#include<set>
#include<map>
#include<vector>
#include<string>
using namespace std;
class DFA
{
	set<int> Q, F;
	set<char> Sigma;
	int q0;
	map< pair< int, char>, int> delta;
	int** partitii;
public:
	DFA();
	DFA(set<int>, set<char>, map<pair<int, char>, int>, int, set<int>);
	int getInitialState();
	void initializarePartitii();
	int** getPartitii();
	set<int> getStates();
	set<int> getFinalState();
	set<char> getSigma();
	map<pair<int, char>, int> getDelta();
	bool isFinalState(int);
	void Partitii();
	void minimizareDFA();
	friend istream& operator >> (istream&, DFA&);

};

