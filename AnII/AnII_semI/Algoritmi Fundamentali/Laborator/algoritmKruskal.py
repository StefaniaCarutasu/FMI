f = open("graf.in")
#LISTA DE ADIACENTA GRAFURI NEORIENTATE PONDERATE
def citireListaPonderi():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    l = []
    i = f.readline()
    while i:
        nod1, nod2, pondere = i.split()     
        nod1, nod2, pondere = int(nod1), int(nod2), int(pondere)
        l.append((nod1, nod2, pondere))
        i = f.readline()
    return n, m, l

def initializare():
   parent.append(0)
   height.append(0)

def reprezentant(nod):
    while parent[nod] != 0:
        nod = parent[nod]
    return nod

def reuneste(u, v):
    ru = reprezentant(u)
    rv = reprezentant(v)

    if height[ru] > height[rv]:
        parent[rv] = ru
    else:
        parent[ru] = rv
        if height[ru] == height[rv]: 
            height[rv] += 1

def Kruskal(muchiiPonderi, nrNoduri):
    #sortez muchiile in ordinea ponderilor
    muchiiPonderi.sort(key = lambda x : x[2])
    
    #initializez varfurile grafului
    for i in range(0, nrNoduri + 1):
        initializare() 
    nrMuchiiAPC = 0     #numarul muchiilor pe care il va avea arborele rezultat
    muchiiAPC = []
    for muchie in muchiiPonderi:        #parcurg muchiile
        if reprezentant(muchie[0]) != reprezentant(muchie[1]):
            muchiiAPC.append(muchie)
            nrMuchiiAPC += 1
            reuneste(muchie[0], muchie[1])      #reunesc extremitatile
            if nrMuchiiAPC == nrNoduri - 1:
                break
    return muchiiAPC    


n, m, muchiiPonderi = citireListaPonderi()
parent = []
height = []

arbore = Kruskal(muchiiPonderi, n)
cost = 0
for muchie in arbore:
    cost += muchie[2]
    print(muchie[0], muchie[1], muchie[2])
    print("Pondere: {}\n".format(cost))