"""
Gramatica:
S -> A
A -> A + C
A -> A - C
A -> C
C -> C * B
C -> C / B
C -> B
B -> ( A )
B -> - B
B -> x
B -> y
B -> z

String-urile de intrare:
x-x*(y+z)
x-x*(xx)
x-(y/x+y/z)/y*(-z)
"""

class Configuration:
    def __init__(self, nonterminal, expression, dot=0, origin=0):
        self.nonterminal = nonterminal
        self.expression = expression
        self.dot = dot
        self.origin = origin

    @property
    def isFinished(self):
        return self.dot >= len(self.expression)

    @property
    def symbol(self):
        if self.isFinished:
            return None
        return self.expression[self.dot]

    @property
    def symbolIsNonterminal(self):
        return self.symbol and self.symbol.isalpha() and self.symbol.isupper()

    @property
    def shift(self):
        return Configuration(self.nonterminal, self.expression, self.dot + 1, self.origin)

    @property
    def tuple(self):
        return self.nonterminal, self.expression, self.dot, self.origin

    def __hash__(self):
        return hash(self.tuple)

    def __eq__(self, other):
        return self.tuple == other.tuple

    def __str__(self):
        n, e, d, o = self.tuple
        return '[%d] %s -> %s.%s' % (o, n, e[:d], e[d:])


class Grammar:
    def __init__(self, rules):
        self.rules = tuple(self.parse(rule) for rule in rules)
        self.start = next(self['S'])

    def parse(self, rule):
        return tuple(rule.replace(' ', '').split('->'))

    def __getitem__(self, nonterminal):
        yield from [
            rule
            for rule in self.rules
            if rule[0] == nonterminal
        ]


def earleayParser(grammar, strToParse):

    # creez tabela de configuratii Earley
    states = [set() for _ in range(len(strToParse) + 1)]

    # adaug starea initiala in lista de configuratii
    states[0].add(Configuration(*grammar.start))

    # folosesc functia enumerate pentru a avea si counter
    for counter, token in enumerate(strToParse + '\0'):
        stateList = list(states[counter])
        states[counter].clear()

        while stateList:
            state = stateList.pop()
            # daca starea exista deja in coloana actuala determinata de valoarea variabilei counter, nu o mai adaugam
            if state in states[counter]:
                continue
            states[counter].add(state)

            # daca ajungem la finalul unei stari (A -> alpha.) in configuratia curenta
            # atunci adaugam la configuratie toate starile care contin (dupa .) starea A -> alpha.
            if state.isFinished:
                stateList = complete(states, state, stateList)

            # daca avem starea A -> alpha.B beta in configuratia curenta
            # atunci orice productie de tipul B -> grama va fi adaugata la configuratia curenta
            if state.symbolIsNonterminal:
                stateList = predict(grammar, state, counter, stateList)

            # se face trecerea la configuratia urmatoare
            # verificam daca urmatorul caracter din sirul de parsat exista intr-o stare din configuratia curenta
            # caracterul trebuie sa aiba punct in fata
            # ex: A -> alpha.a(i+1)beta
            else:
                states = scan(states, state, counter, token)

    isAccepted = False
    for k, state in enumerate(states):
        # verific daca este acceptat cuvantul
        # am ajuns la finalul cuvantului si starea curenta este S
        accepts = any(s.nonterminal == 'S' and s.isFinished for s in state)
        print('Coloana %d:' % k, end=' ')
        print('"%s.%s"' % (strToParse[:k], strToParse[k:]))

        for i in state:
            print('\t', i)
        isAccepted = accepts

    # afisez daca este acceptat cuvantul de catre gramatica sau nu
    if isAccepted:
        print("Cuvantul " + strToParse + " este acceptat")
    else:
        print("Cuvantul " + strToParse + " nu este acceptat")


def complete(states, state, stateList):
    for reduce in states[state.origin]:
        if state.nonterminal == reduce.symbol:
            stateList.append(reduce.shift)

    return stateList


def predict(grammar, state, origin, stateList):
    for rule in grammar[state.symbol]:
        stateList.append(Configuration(*rule, origin=origin))

    return stateList


def scan(states, state, origin, token):
    if state.symbol == token:
        states[origin + 1].add(state.shift)

    return states


def readGrammar():
    f = open("grammar.txt")
    rules = []
    r = f.readline().strip('\n')

    while r:
        rules.append(r)
        r = f.readline().strip('\n')

    f.close()

    return rules


if __name__ == '__main__':
    grammar = Grammar(readGrammar())
    f = open("strings")
    strToParse = f.readline().strip()

    while strToParse:
        print("Se verifica daca este acceptat cuvantul " + strToParse)
        earleayParser(grammar, strToParse)
        strToParse = f.readline().strip()
        print()

    f.close()
