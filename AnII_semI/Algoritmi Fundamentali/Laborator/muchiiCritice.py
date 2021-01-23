
infinit = float("Inf")
f = open("graf.in")
Time = 0
#LISTA DE MUCHII
def citireMuchii():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    mu = {}
    i = f.readline()
    while i:
        x, y= i.split()
        x, y = int(x), int(y)
        if x in mu.keys():
           mu[x].append(y)
        else:
            mu[x] = [y]
        if y in mu.keys():
            mu[y].append(x)
        else:
            mu[y] = [x]
        i = f.readline()
    return n, m, mu


def criticeAux(nod, listaMuchii, visited,  parent, low, disc):
    global Time
    visited[nod] = 1
    disc[nod] = Time
    low[nod] = Time
    Time += 1

    for v in listaMuchii[nod]:
        if visited[v] == 0:
            parent[v] = nod
            criticeAux(v, listaMuchii, visited, parent, low, disc)

            low[nod] = min(low[nod], low[v])
            if low[v] > disc[nod]:
                print(nod, v)
        elif v != parent[nod]:
            low[nod] = min(low[nod], disc[v])


def muchiiCritice(listaMuchii, nrNoduri):
    visited = [0] * (nrNoduri + 1)
    disc = [infinit] * (nrNoduri + 1)
    low = [infinit] * (nrNoduri + 1)
    parent = [0] * (nrNoduri + 1)

    for i in range (1, nrNoduri + 1):
        if visited[i] == 0:
            criticeAux(i, listaMuchii, visited, parent, low, disc)

n, m, muchii = citireMuchii()
print("Muchii critice: ")
muchiiCritice(muchii, n)


