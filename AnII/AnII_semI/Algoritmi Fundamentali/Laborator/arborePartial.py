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

def df_r(nod, graf, nrNoduri, vizitati):
    vizitati[nod] = 1
    for k in range(1, nrNoduri + 1):
        if (k in graf[nod] or nod in graf[k]) and vizitati[k] == 0:
            print(nod, k)
            df_r(k, graf, nrNoduri, vizitati)

n, m, graf = citireGraf()
vizitat = [0] * (n + 1)
df_r(1, graf, n, vizitat)