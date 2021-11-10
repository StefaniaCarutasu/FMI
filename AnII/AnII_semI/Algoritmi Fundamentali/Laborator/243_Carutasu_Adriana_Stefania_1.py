infinit = float("Inf")
f = open("graf.in")
Time = 0
#Pentru fiecare nod verific daca acesta ori este radacina in arborele pentru DFS
#si atunci trebuie sa aiba minim 2 copii pentru a fi punct critic

#Daca nu este radacina si are un copil in subarbore care nu are nicio muchie de intoarcere
#catre un stramos al nodului initial

#Afisez la final punctele critice

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

def pcAux(graf, u, vizitat, ap, tata, low, disc):
    global Time
    copii = 0
    vizitat[u] = 1
    disc[u] = Time
    Time += 1
    for v in graf[u]:
        if vizitat[v] == 0:
            tata[v] = u
            copii += 1
            pcAux(graf, v, vizitat, ap, tata, low, disc)

            low[u] = min(low[u], low[v])

            if tata[u] != 0 and copii > 1:
                ap[u] = 1

            if tata[u] != 0 and low[v] >= disc[u]:
                ap[u] = 1
        elif v != tata[u]:
            low[u] = min(low[u], disc[v])


def puncteCritice(graf, nrNoduri):
    vizitat = [0] * (nrNoduri + 1)
    disc = [float("Inf")] * (nrNoduri + 1)
    low = [float("Inf")] * (nrNoduri + 1)
    tata = [0] * (nrNoduri + 1)
    ap = [0] * (nrNoduri + 1)

    for i in range(1, nrNoduri + 1):
        if vizitat[i] == 0:
            pcAux(graf, i, vizitat, ap, tata, low, disc)
    for i, v in enumerate(ap):
        if v == 1:
            print(i)

n, m, graf = citireMuchii()

puncteCritice(graf, n)
