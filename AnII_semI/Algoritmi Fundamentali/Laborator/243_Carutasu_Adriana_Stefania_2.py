f = open("graf.in")
infinit = float('Inf')

#Calculez distanta de la toate sursele s la toate nodurile folosind algoritmul Dijkstra
#Verific pentru fiecare nod destinatie care este cea mai mica distanta


def citireMuchiiPonderate():
    n, m = f.readline().split() #varfuri si arce
    n, m = int(n), int(m)
    lista = f.readline().split()
    k = int(lista[0])   #numarul de surse
    surse = []
    for i in range(1, k + 1):
        surse.append(int(lista[i]))
    dst = f.readline().split()
    destinatii = []
    for i in dst:
        destinatii.append(int(i))
    mu = []
    matriceAdiacenta = [[]] * (n + 1)
    for i in range(n + 1):
        matriceAdiacenta[i] = [infinit] * (n + 1)
    i = f.readline()
    while i:
        x, y, z = i.split()
        x, y, z = int(x), int(y), int(z)
        mu.append((x, y, z))
        matriceAdiacenta[x][y] = z
        i = f.readline()
    return n, m, mu, matriceAdiacenta, surse, destinatii

def calculareDistanta (muchiiPoderi, nrNoduri, start, matriceAdiacenta, destinatii):
    distanta = [infinit] * (nrNoduri + 1)
    vizitati = [0] * (nrNoduri + 1)
    distanta[start] = 0
    tata = [0] * (nrNoduri + 1)

    for i in range(1, nrNoduri + 1):
        if i in destinatii:
            minim = infinit
            min_index = 0 #min_index va fi nodul urmator din drumul catre nodul destinatie
            for v in range (1, nrNoduri + 1):
                if vizitati[v] == 0 and distanta[v] < minim:
                    minim = distanta[v]
                    min_index = v
                tata[min_index] = start
                start = min_index       
            for v in range (1, nrNoduri + 1): #calculez distanta
                if (vizitati[min_index] == 0 and matriceAdiacenta[min_index][v] and distanta[min_index] != infinit and distanta[min_index] + matriceAdiacenta[min_index][v] < distanta[v]):			    
                    distanta[v] = distanta[min_index] + matriceAdiacenta[min_index][v]
            vizitati[min_index] = 1
    return distanta, tata

def distanteSurseDestinatii(muchiiPoderi, matriceAdiacenta, nrNoduri, surse, destinatii):
    v = []
    for s in surse:
        ma = [[]] * (nrNoduri + 1)
        for i in range(nrNoduri + 1):
            ma[i] = matriceAdiacenta[i]
        dis, tati = calculareDistanta(muchiiPoderi, nrNoduri, s, ma,destinatii)
        d = []
        for i in range(1, nrNoduri + 1):
            if i in destinatii and dis[i] != infinit:
                v.append([s, i, dis[i], tati])
        
    for d in destinatii:
        min = infinit
        drum = []
        for i in v:
            if d == i[1] and i[2] < min:
                drum = i
                min = i[2]
        if min < infinit and len(drum) > 0:
            print("t =", drum[1], "s =", drum[0], "distanta minima =", drum[2], end = " ")

        else:
            print("t = ", d, "nu exista drum din s")
        

        

nrNoduri, nrArce, listaMuchii, matriceAdiacenta, surse, destinatii = citireMuchiiPonderate()

distanteSurseDestinatii(listaMuchii, matriceAdiacenta, nrNoduri, surse, destinatii)