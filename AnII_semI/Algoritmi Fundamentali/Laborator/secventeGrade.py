from collections import deque
f = open("graf.in")
def citire():
    nrNoduri = int(f.readline())
    interne = [int(x) for x in f.readline().split()]
    externe = [int(x) for x in f.readline().split()]
    for i in externe:
        i = int(i)
    return nrNoduri, interne, externe

def crearePartitii(nrNoduri, interne, externe):
    partitii = [0] * (2 * nrNoduri + 3) #pe pozitia 0 nu va fi nimic si ultimele 2 pozitii vor fi s si t
    s = 2 * nrNoduri + 1
    t = 2 * nrNoduri + 2
    partitii[s] = 1
    partitii[t] = 2
    for i in range(1, nrNoduri + 1):
        partitii[i] = 1
    for i in range(nrNoduri + 1, 2 * nrNoduri + 1):
        partitii[i] = 2
    matricePartii = [[]] * (2 * nrNoduri + 3)
    for i in range(2 * nrNoduri + 3):
        matricePartii[i] = [0] * (2 * nrNoduri + 3)
    intr = 0
    extr = 0
    for i in range(1, 2 * nrNoduri + 3):
        for j in range(1, 2 * nrNoduri + 3):
            if i == s and partitii[j] == partitii[s] and len(interne) > intr:
                matricePartii[s][j] = interne[intr]
                intr += 1
            elif j == t and partitii[i] == partitii[t] and len(externe) > extr:
                matricePartii[i][t] = externe[extr]
                extr += 1
            elif partitii[i] < partitii[j] and j - i != nrNoduri and i != s and j != t:
                matricePartii[i][j] = 1
    #for i in matricePartii:
        #print(i)
    return s, t, partitii, matricePartii

def bfs(source, target, parent, nrNoduri, matriceAdiacenta):

    visited = [0] * (nrNoduri + 1)

    queue = deque()
    
    queue.append(source)
    visited[source] = 1
    while queue:
        nod = queue.popleft()
        for j in range(1, nrNoduri + 1):
            if visited[j] == 0 and matriceAdiacenta[nod][j] > 0:
                queue.append(j)
                visited[j] = 1
                parent[j] = nod
            elif visited[j] == 0 and matriceAdiacenta[j][nod] > 0:
                queue.append(j)
                visited[j] = 1
                parent[j] = -nod
    return 1 if visited[target] else 0

def FordFulkerson(source, target, nrNoduri, matriceAdiacenta):
    parent = [0] * (nrNoduri + 1)
    maxFlow = 0
    while bfs( source, target, parent, nrNoduri, matriceAdiacenta):
        pathFlow = float("Inf")
        t = target
        while t != source:
            if parent[t] < 0:
                pathFlow = min(pathFlow, matriceAdiacenta[t][-parent[t]])
                t = -parent[t]
            else: 
                pathFlow = min(pathFlow, matriceAdiacenta[parent[t]][t])
                t = parent[t]

        maxFlow += pathFlow
        t = target
        while t != source:
            if parent[t] < 0:
                u = -parent[t]
                matriceAdiacenta[t][u] += pathFlow
            else: 
                u = parent[t]
                matriceAdiacenta[u][t] -= pathFlow
            t = u
            

    return maxFlow

n, interne, externe = citire()
s, t, partitii, matrice = crearePartitii(n, interne, externe)
n = 2 * n + 2
fm = FordFulkerson(s, t, n, matrice)
print(fm)