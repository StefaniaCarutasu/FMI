f = open("graf.in")
infinit = float('inf')

#LISTA DE MUCHII PONDERATE
def citireMuchiiPond():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    mu = []
    matriceAdiacenta = [[infinit] * (n + 1)] * (n + 1)
    i = f.readline()
    while i:
        x, y, z = i.split()
        x, y, z = int(x), int(y), int(z)
        mu.append((x, y, z))
        matriceAdiacenta[x][y] = z
        i = f.readline()
    return n, m, mu, matriceAdiacenta

def floydWarshall(matriceAdiacenta, nrNoduri):
    dist = matriceAdiacenta
            
    for k in range(nrNoduri):
        for i in range(nrNoduri):
            for j in range(nrNoduri):
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
    
    print(dist)
    print(matriceAdiacenta)



n, m, listaMuchii, matriceAdiacenta = citireMuchiiPond()

floydWarshall(matriceAdiacenta, n)
