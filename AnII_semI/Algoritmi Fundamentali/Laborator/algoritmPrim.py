import sys
from collections import deque
f = open("graf.in")
#LISTA DE ADIACENTA GRAFURI NEORIENTATE PONDERATE
def citireListaPonderi():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    l = []
    i = f.readline()
    while i:
        nod1, nod2, pondere = i.split()     
        nod1, nod2, pondere = int(nod1), int(nod2), int(pondere)
        l.append([nod1, nod2, pondere])
        i = f.readline()
    return n, m, l

def Prim(muchiiPonderi, nrNoduri, infinit, start):
    q = deque()
    muchiiAPC = []
    p = []
    pondere = infinit
    for i in muchiiPonderi:
        if i[0] == start or i[1] == start:
            q.append(i)
    vizitati[start] = 1
    while len(muchiiAPC) < nrNoduri - 1:
        p = []
        pondere = infinit
        for i in q:
            if i[2] < pondere and (vizitati[i[0]] == 0 or vizitati[i[1]] == 0):
                p = i
                pondere = i[2]
        muchiiAPC.append((p[0], p[1], p[2]))
        j = 0
        if vizitati[p[0]] == 0:
            vizitati[p[0]] = 1
            j = p[0]
        else:
            vizitati[p[1]] = 1
            j = p[1]
        for i in q:
            if i == p:
                i[2] = infinit
        for i in muchiiPonderi:
            if (i[0] == j and vizitati[i[1]] == 0) or (i[1] == j and vizitati[i[0]] == 0):
                q.append(i)
    return muchiiAPC
        


infinit = sys.maxsize
n, m, muchiiPonderi = citireListaPonderi()
vizitati = [0] * (n + 1)      #vector de vizitati

arbore = Prim(muchiiPonderi, n, infinit, 1)
cost = 0
for muchie in arbore:
    cost += muchie[2]
    print(muchie[0], muchie[1], muchie[2])
    print("Cost: {}\n".format(cost))