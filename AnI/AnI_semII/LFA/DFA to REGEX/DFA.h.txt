#pragma once
#include <iostream>
#include <map>
#include <string>
#include <set>
#include <fstream>
using namespace std;
class DFA
{
	set<int> Q, F;
	set<string> Sigma;
	int q0;
	map<pair<int, string>, int> delta;

public:
	DFA();
	DFA(set<int>, set<string>, map<pair<int, string>, int>, int, set<int>);
	friend istream& operator >> (istream&, DFA&);
	string dfaToRegex();
};

