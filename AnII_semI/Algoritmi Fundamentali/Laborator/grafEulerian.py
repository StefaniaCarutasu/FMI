from collections import deque
f = open("graf.in")

def citireGraf():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    d = {}
    i = f.readline()
    while i:
        x, y = i.split()
        if x in d.keys():
            d[x].append(y)
        else: d[x] = y
        if y in d.keys():
            d[y].append(x)
        else: d[y] = x
        i = f.readline()
    return n, m, d

def DFS(nod, vizitati, graf, n):
    vizitati[nod] = 1
    for i in graf[nod]:
        if vizitati[i] == 0:
            DFS(i, vizitati, graf, n)

def isConnected(graf, n):
    vizitati = [0] * (n + 1)
    for i in range(n):
        if len(graf[i]) > 1:
            break
    if i == n - 1:
        return 1
    DFS(i, vizitati, graf, n)

    for i in range(n + 1):
        if vizitati[i] == 0 and len(graf[i]) > 0:
            return 0
    return 1

def eulerian(graf, n):
    if isConnected(graf, n) == 0:
        return 0
    else:
        odd = 0
        for i in range(n + 1):
            if len(graf[i]) % 2 != 0:
                odd+=1

    if odd == 0:
        print("Graful nu este eulerian")
    elif odd == 2:
        print("Graful este semieulerian")
    elif odd > 2:
        print("Graful este eulerian")
