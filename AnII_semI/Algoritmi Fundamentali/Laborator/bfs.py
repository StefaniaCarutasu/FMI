from collections import deque
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
#BFS
def bfs(nodStart):
    q = deque()
    q.append(nodStart)
    vizitat[nodStart] = True
    while q:
        nod = q.popleft()
        for j in listaAdiacenta[nod]:
            if vizitat[j] == False:
                vizitat[j] = True
                tata[j] = nod
                q.append(j)
        print(nod, end = ' ')
    print()

#graf conex
def esteConex(listaAdiacenta, nrNoduri):
    nod = 1
    vizitati = [0] * (nrNoduri + 1)
    q = deque()
    vizitat[nod] = 1
    q.append(nod)
    ok = True
    while len(q) > 0:
        nod = q[0]
        q.popleft()
        for i in listaAdiacenta[nod]:
            if vizitati[i] == 0:
                vizitati[i] = 1
                q.append(i)

    for i in range(1, nrNoduri):
        if vizitati[i] == 0:
            ok = False
            break
    if ok:
        print("Este conex")
    else:
        print("Nu este conex")

n, m, listaAdiacenta = citireLista()
vizitat = [0] * (n + 1)      #vector de vizitati
tata = [0] * (n + 1)     #vectori de tati
bfs(1) 

esteConex(listaAdiacenta, n)
