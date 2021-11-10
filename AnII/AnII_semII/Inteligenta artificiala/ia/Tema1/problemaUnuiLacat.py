import os
import sys
import copy
import stopit as stopit
from datetime import datetime


def citireDate(f):
    """
    :param f: fisierul din care citesc datele
    :return: returneaza vectorul de chei (lista de string-uri) si perechea de incuietori truc (lista de int)
    """

    # citim de cate ori putem folosi o cheie
    K = int(f.readline())

    # citim incuietorile cu truc
    incuietoriTruc = f.readline().rstrip('\n')
    truc = [int(x) for x in incuietoriTruc.split('->')]

    chei = []
    # citim cheile
    i = f.readline().rstrip()
    while i:
        chei.append([i, K])
        i = f.readline().rstrip()

    return chei, truc



class NodParcurgere:
    graf = None  # static

    def __init__(self, id, info, parinte, cost, h, truc, chei, cheie):
        self.id = id  # este 0 initial si dupa se incrementeaza
        self.info = info
        self.parinte = parinte  # parintele din arborele de parcurgere
        self.g = cost  # costul de la radacina la nodul curent
        self.h = h  # distanta estimata de la nodul curent pana la nodul final
        self.f = self.g + self.h
        self.truc = truc
        self.chei = chei
        self.cheieUtilizata = cheie


    def aplicaCheie(self, cheie):
        """
        :param cheie: reprezinta cheia folosita pentru a descuia lacatul
        :return: returneaza noua configuratie a lacatului dupa folosirea cheii date ca parametru
        """
        #preiau configuratia actuala a lacatului
        lacat = copy.deepcopy(self.info)
        t1 = self.truc[0]
        t2 = self.truc[1]
        #prima data ma ocup de cazul incuietorilor cu truc
        if cheie[t1] == 'd' and lacat[t1][0] == 'i':       #cazul in care incuietoarea cu truc este descuiata de cheie
            lacat[t1][1] -= 1
            if lacat[t1][1] == 0:
                lacat[t1] = ['d', 0]      #am descuiat incuietoarea de la indice indice_1
            #verific daca incuietoarea de la indice_2 este inchisa
            #daca este inchisa o inchid iar prin incrementarea numarului de inchideri
            #altfel o inchid pentru prima data
            if lacat[t2][0] == 'i':
                lacat[t2][1] += 1
            else:
                lacat[t2] = ['i', 1]
            #verific ce efect are cheia asupra incuietorii de la indice_2
            if cheie[t2] == 'd':
                lacat[t2][1] -= 1
                if lacat[t2][1] == 0:
                    lacat[t2] = ['d', 0]
            elif cheie[t2] == 'i':
                lacat[t2][1] += 1

        else:       #incuietoarea de la indice_1 nu se descuie, asa ca tratez acum incuietorile de la indice_1 si indice_2 pentru a nu mai fi nevoie sa le testez mai tarziu
            #daca indice_1 e deschisa si cheia o inchide atunci o inchid
            if cheie[t1] == 'i' and lacat[t1][0] == 'd':
                lacat[t1] = ['i', 1]
            elif cheie[t1] == 'i' and lacat[t1][0] == 'i':
                lacat[t1][1] += 1
            #daca indice_2 e inchisa si cheia o deschide o deschid
            if cheie[t2] == 'd' and lacat[t2][0] == 'i':
                lacat[t2][1] -= 1
                if lacat[t2][1] == 0:
                    lacat[t2] = ['d', 0]
            # daca indice_2 e deschisa si cheia o inchide atunci o inchid
            elif cheie[t2] == 'i' and lacat[t2][0] == 'd':
                lacat[t2] = ['i', 1]
            elif cheie[t2] == 'i' and lacat[t2][0] == 'i':
                lacat[t2][1] += 1

        #acum pentru fiecare incuietoare ii verific starea actuala si efectul cheii asupra ei
        for c in range(len(cheie)):
            if c == self.truc[0] or c == self.truc[1]:
                pass
            else:
                if cheie[c] == 'i' and lacat[c][0] == 'd':      #daca era deschis si am cheie de inchis inchid
                    lacat[c] = ['i', 1]
                elif cheie[c] == 'd' and lacat[c][0] == 'i':        #daca era inchis ai am cheie de deschis
                    lacat[c][1] -= 1            #descui o singura data
                    if lacat[c][1] == 0:        #daca mi-a ajuns pe 0 atunci zici ca e descuiata
                        lacat[c] = ['d', 0]
                elif cheie[c] == 'i' and lacat[c][0] == 'i':        #daca era inchis si am cheie de inchis actunci inchid iar
                    lacat[c][1] += 1
        return lacat


    def obtineDrum(self):
        l = [self]
        nod = self
        c = 0
        while nod.parinte is not None:
            c += calcCostCurent(nod)
            l.insert(0, nod.parinte)
            nod = nod.parinte
        return l, c


    def afisDrum(self):
        l, c = self.obtineDrum()
        oFile.write("Initial: " + str(l[0]))
        for indice in range(1, len(l) + 1):
            oFile.write(str(indice) + ')')
            oFile.write("Incuietori: " + str(l[indice - 1]))
            if indice != len(l):
                oFile.write("Cheie: " + l[indice].cheieUtilizata + '\n')
                if l[indice].cheieUtilizata[truc[0]] == 'd':
                    oFile.write("Descuierea incuietorii "+ str(truc[0]) + " duce la incuiera incuietorii " + str(truc[1]) + '\n')
            oFile.write('\n')
            indice += 1
        oFile.write("Cost: " + str(c))
        return l

    def contineInDrum(self, infoNodNou):
        nodDrum = self
        while nodDrum is not None:
            if infoNodNou == nodDrum.info:
                return True
            nodDrum = nodDrum.parinte

        return False

    def __str__(self):
        sir = "["
        incuietori = self.info

        for i in range(len(incuietori)):
            sir += "inc(" + incuietori[i][0] + ", " + str(incuietori[i][1]) + ")"
            if i != len(incuietori) - 1:
                sir += ', '
            else:
                sir += "]\n"
        return sir


    def __repr__(self):
        incuietoare = self.__str__()
        #print(incuietoare)
        if self.cheieUtilizata:
            sir = "Incuietori: " + incuietoare + '\n' + "Folosim cheia: " + self.cheieUtilizata + '\n'
        else:
            sir = "Initial: " + incuietoare + '\n'
        return sir


def testareScop(nod):
    """
    :param nod: obiect de tip NodParcurgere
    :return: True daca e scop, False daca nu este
    """
    incuietori = nod.info
    for i in range(len(incuietori)):
        if incuietori[i][0] == 'i':
            return False
    return True

def calcCostCurent(nod):
    """
    :param nod: obiect de tip NodParcurgere
    :return: costul obtinerii unei stari
    """
    curent = nod.info
    vechi = nod.parinte.info
    cost = 0
    for i in range(len(curent)):
        if vechi[i][0] == 'i' and curent[i][0] == 'd':
            cost += 1
    return cost

def euristicaBanala(nod):
    """
    :param nod: obiect de tip NodParcurgere
    :return: returneaza 1 daca nu este nod scop si 0 altfel (int)
    """
    if testareScop(nod):
        return 0
    return 1

# toate incuietorile sunt inca inchise
def euristicaInadmisibila(nod):
    """
    :param nod:  obiect de tip NodParcurgere
    :return: returneaza mereu numarul total de incuietori (int)
    """
    stare = nod.info
    return len(stare)

# mai am de descuiat doar cele incuiate
def euristicaAdmisibila1(nod):
    """
    :param nod: obiect de tip NodParcurgere
    :return: suma reprezentand cate incuietori mai am de deschis (int)
    """
    stare = nod.info
    cost = 0
    for j in stare:
        cost += j[1]
    return cost

# presupun ca am folosit o cheie truc care mi-a descuiat o incuietoare si a incuiat alta
def euristicaAdmisibila2(nod):
    """
    :param nod: obiect de tip NodParcurgere
    :return: int
    Daca incuietoarea este inchisa, costul creste cu 1
    """
    stare = nod.info
    cost = 0
    for i in range(len(stare)):
        if stare[i][0] == 'i':
            cost += 1
    return cost


class Graph:  # graful problemei
    def __init__(self, start, scop):
        self.noduri = [start, scop]
        self.nrNoduri = 2
        self.start = start
        self.scop = scop
        self.lista_h = [0, 0]

    def indiceNod(self, n):
        return self.noduri.index(n)

    # va genera succesorii sub forma de noduri in arborele de parcurgere
    def genereazaSuccesori(self, nodCurent, euristica = "banala"):
        """
        :param nodCurent: obiect de tip NodParcurgere care reprezinta nodul curent
        :param euristica: euristica pe care o folosesc
        :return: lista de obiecte de tip NodParcurgere

        Aplic fiecare cheie disponibila (care are K > 0) pe nodul curent.
        Pentru fiecare configuratie rezultata voi crea un nou obiect de tip NodParcurgere si schimb valoarea K a cheii folosite.
        Adaug nodul in lista de succesori.
        """
        listaSuccesori = []

        id = nodCurent.id + len(chei)

        for c in range(len(nodCurent.chei)):
            if(nodCurent.chei[c][1] != 0):
                #aplic cheia pe incuietori ca sa obtin o incuietoare noua
                nodNou = nodCurent.aplicaCheie(nodCurent.chei[c][0])    #imi intoarce un string
                cheite = copy.deepcopy(nodCurent.chei)
                cheite[c][1] -= 1

                succ = NodParcurgere(
                    id=id,
                    info=nodNou,
                    parinte=nodCurent,
                    truc=nodCurent.truc,
                    chei=cheite,
                    cheie=chei[c][0],
                    cost=0,
                    h=0
                )

                succ.cost = nodCurent.g + calcCostCurent(succ)
                self.calculeaza_h(succ, euristica)
                succ.f = succ.cost + succ.h
                listaSuccesori.append(succ)

                id += 1

        return listaSuccesori

    def calculeaza_h(self, nod, euristica = 'banala'):
        """
        :param nod: obiect de tip NodParcurgere
        :param euristica: euristica folosita
        :return: int reprezentand valoarea h a nodului primit ca parametru
        """

        if euristica == 'banala':
            nod.h += euristicaBanala(nod)
        elif euristica == 'admisibila1':
            nod.h += euristicaAdmisibila1(nod)
        elif euristica == "inadmisibila":
            nod.h += euristicaInadmisibila(nod)
        else:
            nod.h += euristicaAdmisibila2(nod)
        return nod.h

    def __repr__(self):
        sir = ""
        for (k, v) in self.__dict__.items():
            sir += "{} = {}\n".format(k, v)
        return sir

f = sys.argv[1]
g = sys.argv[2]

NSOL = int(sys.argv[3])
to = int(sys.argv[4])

iFile = open(f)
oFile = open(g, 'w')

chei, truc = citireDate(iFile)

if len(truc) > 2:
    print("Nu ati introdus bine incuietoarea cu truc")
    exit()
l = len(chei[0][0])
for c in chei:
    if len(c[0]) != l:
        print("Nu toate cheile au aceeasi lungime")
        exit()
    for i in c[0]:
        if (i != 'i' and i != 'g') and i != 'd':
            print("Cheia nu respecta formatul")
            exit()

# am incuietorile in starea initiala cand toate sunt incuiate
incuietori = [['i', 1] for i in range(len(chei[0][0]))]
# starea initiala cu toate incuiate
stareInitiala = copy.deepcopy(incuietori)

# starea finala cu toate descuiate
stareFinala = [['d', 0] for j in range(len(chei[0][0]))]
gr = Graph(stareInitiala, stareFinala)


@stopit.threading_timeoutable(default="timeout")
def a_star(gr, euristica = 'banala'):
    durata = datetime.now()
    # in coada vom avea doar noduri de tip NodParcurgere (nodurile din arborele de parcurgere)
    nod = NodParcurgere(
        gr.noduri.index(gr.start), gr.start, None, 0, 0, truc, chei, None
    )
    gr.calculeaza_h(nod)
    c = [nod]

    while len(c) > 0:

        nodCurent = c.pop(0)

        if testareScop(nodCurent):
            final = datetime.now()
            print("Solutie: ", end="")
            print("Solutia a fost gasita dupa ", final-durata)
            nodCurent.afisDrum()

        lSuccesori = gr.genereazaSuccesori(nodCurent, euristica)
        for s in lSuccesori:
            i = 0
            while i < len(c):
                if c[i].f >= s.f:
                    break
                i += 1
            c.insert(i, s)


# solutia optima A*
@stopit.threading_timeoutable(default="timeout")
def a_star_optimizat(gr, euristica = 'banala'):
    durata = datetime.now()
    # coada OPEN
    nod = NodParcurgere(
        gr.noduri.index(gr.start), gr.start, None, 0, 0, truc, chei, None
    )
    gr.calculeaza_h(nod)
    c = [nod]
    closed = []

    while len(c) > 0:

        nodCurent = c.pop(0)
        closed.append(nodCurent)

        if testareScop(nodCurent):
            final = datetime.now()
            print("Solutie: ", end="")
            print("Timp: ", final - durata)
            nodCurent.afisDrum()
            return

        lSuccesori = gr.genereazaSuccesori(nodCurent, euristica)
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


@stopit.threading_timeoutable(default="timeout")
def uniform_cost(gr, nrSolutiiCautate=1, euristica = 'banala'):
    durata = datetime.now()
    # in coada vom avea doar noduri de tip NodParcurgere (nodurile din arborele de parcurgere)
    nod = NodParcurgere(
        gr.noduri.index(gr.start), gr.start, None, 0, 0, truc, chei, None
    )
    gr.calculeaza_h(nod)
    c = [nod]
    nsol = nrSolutiiCautate
    while len(c) > 0:
        nodCurent = c.pop(0)

        if testareScop(nodCurent):
            print("Solutie: ", end="")
            final = datetime.now()
            nodCurent.afisDrum()
            nrSolutiiCautate -= 1
            print("Solutia ", nsol - nrSolutiiCautate, " a fost gasita dupa ", final - durata)
            if nrSolutiiCautate == 0:
                return
        lSuccesori = gr.genereazaSuccesori(nodCurent, euristica)
        for s in lSuccesori:
            i = 0
            while i < len(c):
                if c[i].g > s.g:
                    break
                i += 1
            c.insert(i, s)

@stopit.threading_timeoutable(default="timeout")
def ida_star(gr, nrSolutiiCautate, euristica = 'banala'):
    durata = datetime.now()
    nod = NodParcurgere(
        gr.noduri.index(gr.start), gr.start, None, 0, 0, truc, chei, None
    )
    limita = gr.calculeaza_h(nod)

    while True:
        nrSolutiiCautate, rez = construieste_drum(
            gr, nod, limita, nrSolutiiCautate, durata, euristica
        )
        if rez == "gata":
            break
        if rez == float("inf"):
            oFile.write("Nu exista solutii")
            print("Nu exista suficiente solutii!")
            break
        limita = rez


def construieste_drum(gr, nodCurent, limita, nrSolutiiCautate, durata, euristica = 'banala'):
    nsol = nrSolutiiCautate
    if nodCurent.f > limita:
        return nrSolutiiCautate, nodCurent.f
    if testareScop(nodCurent) and nodCurent.f == limita:
        final = datetime.now()
        print("Solutie: ")
        nodCurent.afisDrum()
        nrSolutiiCautate -= 1
        print("Solutia ", nsol - nrSolutiiCautate, " a fost gasita dupa ", final - durata)
        if nrSolutiiCautate == 0:
            return nrSolutiiCautate, "gata"
    lSuccesori = gr.genereazaSuccesori(nodCurent, euristica)
    minim = float("inf")
    for s in lSuccesori:
        nrSolutiiCautate, rez = construieste_drum(gr, s, limita, durata, nrSolutiiCautate)
        if rez == "gata":
            return nrSolutiiCautate, "gata"
        if rez < minim:
            minim = rez
    return nrSolutiiCautate, minim


#APELURI FUNCTII
#uniform_cost(gr, NSOL, 'admisibila1', timeout = to)
#a_star(gr, 'inadmisibila', timeout = to)
a_star_optimizat(gr, 'banala', timeout = to)
#ida_star(gr, NSOL, 'admisibila2', timeout = to)

if os.stat(g).st_size == 0:
    oFile.write("TIMEOUT: " + str(to))



