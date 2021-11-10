"""
Observatie pentru cei absenti la laborator: trebuie sa dati enter după fiecare afișare a cozii până vă apare o soluție. Afișarea era ca să vedem progresul algoritmului. Puteți să o dezactivați comentând print-ul cu coada și input()
"""


# informatii despre un nod din arborele de parcurgere (nu din graful initial)
class NodParcurgere:
    graf = None  # static

    def __init__(self, id, info, parinte, cost, h):
        self.id = id  # este indicele din vectorul de noduri
        self.info = info
        self.parinte = parinte  # parintele din arborele de parcurgere
        self.g = cost  # costul de la radacina la nodul curent
        self.h = h  # distanta estimata de la nodul curent pana la nodul final
        self.f = self.g + self.h

    def obtineDrum(self):
        l = [self.info]
        nod = self
        while nod.parinte is not None:
            l.insert(0, nod.parinte.info)
            nod = nod.parinte
        return l

    def afisDrum(self):  # returneaza si lungimea drumului
        l = self.obtineDrum()
        print(("->").join(l))
        print("Cost: ", self.g)
        return len(l)

    def contineInDrum(self, infoNodNou):
        nodDrum = self
        while nodDrum is not None:
            if infoNodNou == nodDrum.info:
                return True
            nodDrum = nodDrum.parinte

        return False

    def __repr__(self):
        sir = ""
        sir += self.info + "("
        sir += "id = {}, ".format(self.id)
        sir += "drum="
        drum = self.obtineDrum()
        sir += ("->").join(drum)
        sir += " g:{}".format(self.g)
        sir += " h:{}".format(self.h)

        sir += " f:{})".format(self.f)
        return sir


class Graph:  # graful problemei
    def __init__(
            self, noduri, matriceAdiacenta, matricePonderi, start, scopuri, lista_h
    ):
        self.noduri = noduri
        self.matriceAdiacenta = matriceAdiacenta
        self.matricePonderi = matricePonderi
        self.nrNoduri = len(matriceAdiacenta)
        self.start = start
        self.scopuri = scopuri
        self.lista_h = lista_h

    def indiceNod(self, n):
        return self.noduri.index(n)

    def testeaza_scop(self, nodCurent):
        return nodCurent.info in self.scopuri

    # va genera succesorii sub forma de noduri in arborele de parcurgere
    def genereazaSuccesori(self, nodCurent):
        listaSuccesori = []
        for i in range(self.nrNoduri):
            if self.matriceAdiacenta[nodCurent.id][i] == 1 \
               and not nodCurent.contineInDrum(self.noduri[i]):
                nodNou = NodParcurgere(
                    i,
                    self.noduri[i],
                    nodCurent,
                    nodCurent.g + self.matricePonderi[nodCurent.id][i],
                    self.calculeaza_h(self.noduri[i]),
                )
                listaSuccesori.append(nodNou)
        return listaSuccesori

    def calculeaza_h(self, infoNod):
        return self.lista_h[self.indiceNod(infoNod)]

    def __repr__(self):
        sir = ""
        for (k, v) in self.__dict__.items():
            sir += "{} = {}\n".format(k, v)
        return sir


##############################################################################################
#                                 Initializare problema                                      #
##############################################################################################

# pozitia i din vectorul de noduri da si numarul liniei/coloanei corespunzatoare din matricea de adiacenta
noduri = ["a", "b", "c", "d", "e", "f", "g"]

m = [
    [0, 1, 0, 1, 0, 0, 0],
    [0, 0, 0, 1, 1, 0, 1],
    [0, 0, 0, 0, 0, 1, 0],
    [0, 1, 1, 0, 0, 1, 0],
    [0, 0, 1, 0, 0, 1, 0],
    [0, 0, 0, 1, 0, 0, 0],
    [0, 0, 0, 0, 1, 1, 0],
]
mp = [
    [0, 5, 0, 3, 0, 0, 0],
    [0, 0, 0, 5, 17, 0, 11],
    [0, 0, 0, 0, 0, 3, 0],
    [0, 1, 24, 0, 0, 18, 0],
    [0, 0, 6, 0, 0, 10, 0],
    [0, 0, 0, 3, 0, 0, 0],
    [0, 0, 0, 0, 4, 22, 0],
]
start = "a"
scopuri = ["f"]
# exemplu de euristica banala (1 daca nu e nod scop si 0 daca este)
vect_h = [0, 3, 3, 10, 6, 0, 13]

gr = Graph(noduri, m, mp, start, scopuri, vect_h)
NodParcurgere.graf = gr


def a_star(gr, nrSolutiiCautate=4):
    # in coada vom avea doar noduri de tip NodParcurgere (nodurile din arborele de parcurgere)
    c = [
        NodParcurgere(
            gr.noduri.index(gr.start), gr.start, None, 0, gr.calculeaza_h(gr.start)
        )
    ]

    while len(c) > 0:
        print("Coada actuala: " + str(c))
        input()
        nodCurent = c.pop(0)

        if gr.testeaza_scop(nodCurent):
            print("Solutie: ", end="")
            nodCurent.afisDrum()
            print("\n----------------\n")
            input()
            nrSolutiiCautate -= 1
            if nrSolutiiCautate == 0:
                return

        lSuccesori = gr.genereazaSuccesori(nodCurent)
        for s in lSuccesori:
            i = 0
            while i < len(c):
                # diferenta fata de UCS e ca ordonez dupa f
                if c[i].f >= s.f:
                    break
                i += 1
            c.insert(i, s)


# solutia optima A*
def a_star_optimizat(gr):
    # coada OPEN
    c = [
        NodParcurgere(
            gr.noduri.index(gr.start), gr.start, None, 0, gr.calculeaza_h(gr.start)
        )
    ]
    closed = []

    while len(c) > 0:
        print("Coada actuala: " + str(c))
        print("Coada closed: " + str(closed))
        input()

        nodCurent = c.pop(0)
        closed.append(nodCurent)

        if gr.testeaza_scop(nodCurent):
            print("Solutie: ", end="")
            nodCurent.afisDrum()
            print("\n--------------------\n")
            return

        lSuccesori = gr.genereazaSuccesori(nodCurent)
        lSuccesoriCopy = lSuccesori.copy()
        for s in lSuccesoriCopy:
            gasitOpen = False
            for elem in c:
                if s.info == elem.info:
                    gasitOpen = True
                    if s.f < elem.f:
                        c.remove(elem)
                    else:
                        lSuccesori.remove(s)
                    break

            if not gasitOpen:
                for elem in closed:
                    if s.info == elem.info:
                        if s.f < elem.f:
                            closed.remove(elem)
                        else:
                            lSuccesori.remove(s)
                        break

        for s in lSuccesori:
            i = 0
            while i < len(c):
                if c[i].f >= s.f:
                    break
                i += 1
            c.insert(i, s)

# a_star(gr) # mai multe colutii
a_star_optimizat(gr) # cea mai buna solutie