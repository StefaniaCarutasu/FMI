class FiniteTranslator:
    def __init__(self, Q, Vi, Ve, delta, s, F):
        self.Q = Q
        self.Vi = Vi
        self.Ve = Ve
        self.delta = delta
        self.s = s
        self.F = F
        self.currentState = s
        self.lambdaSymbol = '#'
        self.outputs = []

    def isFinalState(self, state):
        """
           :param state: starea curenta a translatorului

           :return:
           bool: Verifica daca starea curenta primita ca parametru este o stare finala
        """
        return state in self.F

    def resetTranslator(self):
        """
            reseteaza translatorul pentru a putea verifica a-l folosi ulterior pentru restul string-urilor
        """
        self.currentState = s
        self.outputs = []

    def deltaStar(self, state, stringI, stringO):
        """
            :param state: starea curenta
            :param stringI: string-ul de input in forma curenta
            :param stringO: string-ul de iesire in forma curenta

            verifica daca a fost prelucrat intregul string de input si daca s-a ajuns la stare finala
            daca nu s-a ajuns la stare finala este facuta urmatoarea tranzitie din starea curenta in toate starile posibile
        """
        if stringI == self.lambdaSymbol and self.isFinalState(state):
            self.outputs.append(stringO)
        elif stringI != self.lambdaSymbol:
            currentSymbol = stringI[0]
            stringI = stringI[1:]
            for i in delta[(state, currentSymbol)]:
                if i[0] != "#":
                    stringO += i[0]
                newState = i[1]

                self.deltaStar(newState, stringI, stringO)

    def printTranslator(self):
        """
            afiseaza translatorul
        """
        print("Q: {", end='')
        for i in self.Q:
            if i != self.Q[-1]:
                print(i, end=', ')
            else:
                print(i, end='}')
        print()

        print("Vi: {", end='')
        for i in self.Vi:
            if i != self.Vi[-1]:
                print(i, end=', ')
            else:
                print(i, end='}')
        print()

        print("Ve: {", end='')
        for i in self.Ve:
            if i != self.Ve[-1]:
                print(i, end=', ')
            else:
                print(i, end='}')
        print()

        print("Delta: {")
        for i in self.delta.keys():
            print("(", i, ": ", self.delta[i], ")")
        print("}")

        print("S:", self.s)

        print("F: {", end='')
        for i in self.F:
            if i != self.F[-1]:
                print(i, end=', ')
            else:
                print(i, end='}')
        print()


def readTranslator():
    f = open("translator.txt")

    Q = f.readline().strip().split(' ')
    Vi = f.readline().strip().split(' ')
    Ve = f.readline().strip().split(' ')

    noOfTransitions = int(f.readline())
    delta = dict()

    for i in range(noOfTransitions):
        t = f.readline().strip().split(' ')
        if (t[0], t[1]) in delta.keys():
            delta[(t[0], t[1])].append((t[2], t[3]))
        else:
            delta[(t[0], t[1])] = [(t[2], t[3])]

    s = f.readline().strip()
    F = f.readline().strip().split(' ')

    f.close()

    return Q, Vi, Ve, delta, s, F


def readStrings():
    g = open("strings.txt")

    strings = []
    i = g.readline().strip()

    while i:
        strings.append(i)
        i = g.readline().strip()

    g.close()

    return strings


if __name__ == "__main__":
    Q, Vi, Ve, delta, s, F = readTranslator()
    T = FiniteTranslator(Q, Vi, Ve, delta, s, F)

    T.printTranslator()

    strings = readStrings()
    for w in strings:
        T.deltaStar(T.s, w + "#", "")
        print("T({string})=".format(string=w), end='')
        print(T.outputs)

        T.resetTranslator()
