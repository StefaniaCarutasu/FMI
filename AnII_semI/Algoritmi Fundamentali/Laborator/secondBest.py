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

def initializare(height, parent):
   parent.append(0)
   height.append(0)

def reprezentant(nod, height, parent):
    while parent[nod] != 0:
        nod = parent[nod]
    return nod

def reuneste(u, v, height, parent):
    ru = reprezentant(u, height, parent)
    rv = reprezentant(v, height, parent)

    if height[ru] > height[rv]:
        parent[rv] = ru
    else:
        parent[ru] = rv
        if height[ru] == height[rv]: 
            height[rv] += 1

def Kruskal(muchiiPonderi, nrNoduri):
    #sortez muchiile in ordinea ponderilor
    muchiiPonderi.sort(key = lambda x : x[2])
    height = []
    parent = []
    #initializez varfurile grafului
    for i in range(0, nrNoduri + 1):
        initializare(height, parent) 
    nrMuchiiAPC = 0     #numarul muchiilor pe care il va avea arborele rezultat
    muchiiAPC = []
    for muchie in muchiiPonderi:        #parcurg muchiile
        if reprezentant(muchie[0], height, parent) != reprezentant(muchie[1], height, parent):
            muchiiAPC.append(muchie)
            nrMuchiiAPC += 1
            reuneste(muchie[0], muchie[1], height, parent)      #reunesc extremitatile
            if nrMuchiiAPC == nrNoduri - 1:
                break
    return muchiiAPC    

def calculareCost(arborePartial):
    cost = 0
    for muchie in arborePartial:
        cost += muchie[2]
    return cost

def secondBest(muchiiPonderi, nrNoduri):
    muchiiAPCM = Kruskal(muchiiPonderi, nrNoduri) #asa arata APCM ul
    muchiiSB = []
    for i in muchiiPonderi:
        muchiiSB.append((i[0], i[1], i[2]))
    costSB = calculareCost(muchiiSB)
    for muchie in muchiiAPCM:
        newMuchii = []
        for i in muchiiPonderi:
            if i != muchie:
                newMuchii.append((i[0], i[1], i[2]))
        newMuchii = Kruskal(newMuchii, len(newMuchii))
        newCost = calculareCost(newMuchii)
        if newCost < costSB:
            costSB = newCost
            muchiiSB = newMuchii

    return muchiiSB, costSB

n, m, muchiiPonderi = citireListaPonderi()

apcm = Kruskal(muchiiPonderi, n)

sb, costSB = secondBest(muchiiPonderi, n)
print(costSB)
#print(calculareCost(sb))