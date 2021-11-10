f = open("graf.in")

def citireGraf():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    i = f.readline()
    d = {}
    while i:
        x, y = i.split()
        x, y = int(x), int(y)
        if x in d.keys():
            d[x].append(y)
        else:
            d[x] = [y]
        i = f.readline()

    return n, m, d

def ciclicAux(graf, nod, vizitat, stiva):
    vizitat[nod] = 1
    stiva[nod] = 1

    if nod in graf.keys():
        for n in graf[nod]:
            if vizitat[n] == 0:
                if ciclicAux(graf, n, vizitat, stiva) == 1:
                    return 1
            elif stiva[n] == 1 :
                return 1
    stiva[nod] = 0
    return 0

def ciclic(graf, nrNoduri):
    vizitat = [0] * (nrNoduri + 1)
    stiva = [0] * (nrNoduri + 1)
    for n in range(1, nrNoduri + 1):
        if vizitat[n] == 0:
            if ciclicAux(graf, n, vizitat, stiva) == 1:
                return True
    return False

n, m, muchii = citireGraf()
print(muchii)
if ciclic(muchii, n) == 1:
    print("Contine cicluri")
else:
    print("Este aciclic")