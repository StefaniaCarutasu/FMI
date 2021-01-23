from collections import deque
f = open("graf.in")

def citireGraf():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    g = [[]] * (n + 1)
    for i in range(n + 1):
        g[i] = [0] * (n + 1)
    mu = []
    i = f.readline()
    while i:
        x, y, z= i.split()
        x, y, z = int(x), int(y), int(z)
        g[x][y] = z
        g[y][x] = z
        mu.append((x, y))
        i = f.readline()
    
    return n, m, g, mu

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


def partitii(graf, src, n):
    culori = [-1] * (n + 1)
    culori[src] = 1
    q = deque()
    q.append(src)
    while q:
        u = q.popleft()

        if graf[u][u] == 1:
            return False
        
        for v in range(n + 1):
            if graf[u][v] != 0 and culori[v] == -1:
                culori[v] = 1 - culori[u]
                q.append(v)
            elif graf[u][v] != 0 and culori[v] == culori[u]:
                return False

    return True, culori


n, m, g, muchii = citireGraf()
b, vectorPartitii = partitii(g, 1, n)
if b:  #este bipartit
    grafDeCuplaje = []
    for i in vectorPartitii:
        grafDeCuplaje.append(i)
    grafDeCuplaje.append(1)     #sursa
    grafDeCuplaje.append(0)     #destinatie
    nrNoduriGrafCuplaje = n + 2     #am inca 2 noduri in plus, s si t dar
    s = len(grafDeCuplaje) - 2
    t = len(grafDeCuplaje) - 1
    matriceCuplaje = [[]] * (nrNoduriGrafCuplaje + 1)
    for i in range(nrNoduriGrafCuplaje + 1):
        matriceCuplaje[i] = [0] * (nrNoduriGrafCuplaje + 1)
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            matriceCuplaje[i][j] = g[i][j] #copiez matricea initiala
    for i in range(1, nrNoduriGrafCuplaje + 1):
        if grafDeCuplaje[i] == grafDeCuplaje[s] and i != s:
            matriceCuplaje[s][i] = 1
        elif grafDeCuplaje[i] == grafDeCuplaje[t] and i != t:
            matriceCuplaje[i][t] = 1
    
    fm = FordFulkerson(s, t, nrNoduriGrafCuplaje, matriceCuplaje)
    for i in muchii:
        if matriceCuplaje[i[0]][i[1]] == 0:
            print(i[0], "->", i[1])
else:
    print("Nu este bipartit")
