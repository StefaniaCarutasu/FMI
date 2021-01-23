import sys
f = open("graf.in")
infinit = float('inf')

#LISTA DE MUCHII PONDERATE
def citireMuchiiPond():
    n, m = f.readline().split()
    n, m = int(n), int(m)
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
    return n, m, mu, matriceAdiacenta

def dijkstra (muchiiPoderi, nrNoduri, start):
    distanta = [infinit] * (nrNoduri + 1)
    vizitati = [0] * (nrNoduri + 1)
    distanta[start] = 0

    for i in range(1, nrNoduri + 1):
        minim = infinit
        min_index = 0
        for v in range (1, nrNoduri + 1):
            if vizitati[v] == 0 and distanta[v] < minim:
                minim = distanta[v]
                min_index = v
        
        for v in range (1, nrNoduri + 1):
            if (vizitati[min_index] == 0 and matriceAdiacenta[min_index][v] and distanta[min_index] != infinit and distanta[min_index] + matriceAdiacenta[min_index][v] < distanta[v]):			    
                distanta[v] = distanta[min_index] + matriceAdiacenta[min_index][v]
        vizitati[min_index] = 1
 
    return distanta  

n, m, muchiiPoderi, matriceAdiacenta = citireMuchiiPond()
distante= dijkstra(muchiiPoderi, n, 1)

print(distante[1:n+1])