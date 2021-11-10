f = open("graf.in")
#LISTA DE ADIACENTA GRAFURI NEORIENTATE
def citireLista():
    n, m = f.readline().split()         #nr de noduri si muchii
    n, m = int(n), int(m)
    d = {}
    i = f.readline()        #citim varfurile muchiilor
    while i:
        x, y = i.split() 
        x, y = int(x), int(y)
        if x in d:      #pastram lista de adiacenta ca un dictionar
            d[x].append(y)
        else:
            d[x] = [y]
        if y in d:
            d[y].append(x)
        else:
            d[y] = [x]
        i = f.readline()
    return n, m, d      #intoarcem numarul de nodurii, muchii si lista

#DFS
def dfs(nod):
    print(nod)
    vizitat[nod] =1
    if nod in listaAdiacenta:
        for v in listaAdiacenta[nod]:
            if vizitat[v] == 0:
                tata[v] = nod
                dfs(v)

n, m, listaAdiacenta = citireLista()
vizitat = [0] * (n + 1)      #vector de vizitati
tata = [0] * (n + 1)     #vector de tati
dfs(1) 