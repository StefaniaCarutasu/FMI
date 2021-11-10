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
        matriceAdiacenta[x][x] = 0
        matriceAdiacenta[y][y] = 0
        i = f.readline()
    return n, m, mu, matriceAdiacenta

def BellmanFord(matriceAdiacenta, muchii, nrNoduri, start):
    dist = [infinit] * (nrNoduri + 1)
    dist[start] = 0

    for i in range(nrNoduri - 1):
        for u, v, w in muchii:  
            if dist[u] != infinit and dist[u] + w < dist[v]:  
                dist[v] = dist[u] + w 

    for u, v, w in muchii:  
        if dist[u] != infinit and dist[u] + w < dist[v]:  
            print("Graph contains negative weight cycle") 
            return
    print("Nod \t Distanta de la sursa")  
    for i in range(1, nrNoduri):  
        print("{}\t\t\t\t\t\t\t{}".format(i, dist[i]))

n, m, muchii, matriceAdiacenta = citireMuchiiPond()

BellmanFord(matriceAdiacenta, muchii, n, 1)