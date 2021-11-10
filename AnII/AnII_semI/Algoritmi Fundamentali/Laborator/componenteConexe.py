f = open("graf.in")

#LISTA DE MUCHII PONDERATE
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
        else:
            d[x] = [y]
        if y in d.keys():
            d[y].append(x)
        else:
            d[y] = [x]
        i = f.readline()
    return n, m, d

def DFS(graf, temp, nod, visited):
    visited[nod] = 1
    temp.append(nod)
    for i in graf[nod]:
        if visited[i] == 0:
            temp = DFS(graf, temp, i, visited)
    return temp

def componenteConexe(graf, n):
    visited = [0] * (n + 1)
    cc = []
    for i in range(1,n+1):
        if visited[i] == 0:
            temp = []
            cc.append(DFS(graf, temp, i, visited))

    return cc


n, m, graf = citireGraf()
visited = [0] * (n + 1)
print(componenteConexe(graf, n))