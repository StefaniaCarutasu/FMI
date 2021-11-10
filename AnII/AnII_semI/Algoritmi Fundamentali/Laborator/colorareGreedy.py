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

def culori(graf, nrNoduri, s):
    vizitati = [0] * (nrNoduri + 1)
    culori = [0] * (nrNoduri + 1)
    culori[s] = 1
    coada = deque()
    coada.append(s)
    while coada:
        nod = coada.popleft()
        if vizitati[nod] == 0:
            vizitati[nod] = 1
        for i in graf[nod]:
            if vizitati[i] == 0 and culori[i] == 0:
                culori[i] = 2 - culori[nod]
                coada.append(i)
            if vizitati[i] and culori[i] == culori[nod]:
                culori[nod] += 1

    for i in range(1, nrNoduri + 1):
        print(i, " -> ", culori[i])


n, m, G = citireGraf()
culori(G, n, 1)