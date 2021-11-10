from collections import deque
f = open("graf.in")
def citireGraf():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    d = {}
    i = f.readline()
    while i:
        x, y = i.split()
        x, y = int(x), int(y)
        if x in d.keys():
            d[x].append(y)
        else: d[x] = [y]
        if y in d.keys():
            d[y].append(x)
        else: d[y] = [x]
        i = f.readline()
    return n, m, d

def isSafe(graf, nrNoduri, nod, culori, c):
    for i in range(1, nrNoduri + 1):
        if i in graf[nod] and culori[i] == c:
            return 0
    return 1

def colorareAux(graf, nrNoduri, m, culori, nod):
    if nod == nrNoduri + 1:
        return 1
    for c in range(1, m + 1):
        if isSafe(graf, nrNoduri, nod, culori, c) == 1:
            culori[nod] = c
            if colorareAux(graf, nrNoduri, m, culori, nod + 1) == 1:
                return 1
            culori[nod] = 0

def colorare(graf, nrNoduri, m):
    culori = [0] * (nrNoduri + 1)
    if colorareAux(graf, nrNoduri, m, culori, 1) == None:
        return False
    
    print("Solutia exista si acestea sunt culorile: ")
    print("Nod\t\tCuloare")
    for i in range (1, nrNoduri + 1):
        print(i, " -> ", culori[i])

 
n, m, graf = citireGraf()
for i in graf.keys():
    print(i, graf[i])
colorare(graf, n, 6)