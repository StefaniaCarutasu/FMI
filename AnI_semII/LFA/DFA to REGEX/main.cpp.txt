#include "DFA.h"
#include<fstream>
ifstream f("dfa.txt");
int main()
{
	DFA D;
	f >> D;
	string regex;
	regex = D.dfaToRegex();
	cout << regex;
	return 0;
}
