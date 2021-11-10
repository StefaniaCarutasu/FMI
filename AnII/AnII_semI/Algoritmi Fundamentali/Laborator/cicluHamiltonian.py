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

def isSafe(graf, nod, poz, cale):
    if graf[cale[poz - 1]][nod] == 0:
        return 0

    for v in cale:
        if v == nod:
            return 0
    return 1

def cicluH(graf, cale, poz, n):
    if poz == n:
        if graf[cale[poz - 1]][cale[0]] == 1:
            return 1
        else: return 0
    for v in range(2, n + 1):
        if isSafe(graf, v, poz, cale) == 1:
            cale[poz] = v
            if cicluH(graf, cale, poz + 1, n) == 1:
                return 1
            cale[poz] = -1
    return 0

#def hamiltonian(graf, n):

    



