from collections import deque
f = open("graf.in")
#LISTA DE MUCHII PONDERATE
def citireMuchiiPond():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    mu = []
    matriceAdiacenta = [[]] * (n + 1)
    for i in range(n + 1):
        matriceAdiacenta[i] = [0] * (n + 1)
    i = f.readline()
    while i:
        x, y, z = i.split()
        x, y, z = int(x), int(y), int(z)
        mu.append((x, y, z))
        matriceAdiacenta[x][y] = z
        i = f.readline()
    return n, m, mu, matriceAdiacenta

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

n, m, muchiiCapacitati, matriceAdiacenta = citireMuchiiPond()
fm = FordFulkerson(1, 6, n, matriceAdiacenta)
print("Fluxul maxim este: ", fm)
    
