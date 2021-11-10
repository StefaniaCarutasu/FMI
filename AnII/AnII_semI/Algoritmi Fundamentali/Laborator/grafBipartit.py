from collections import deque
f = open("graf.in")

def citireGraf():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    g = [[]] * (n + 1)
    for i in range(n + 1):
        g[i] = [0] * (n + 1)
    
    i = f.readline()
    while i:
        x, y, z= i.split()
        x, y, z = int(x), int(y), int(z)
        g[x][y] = z
        g[y][x] = z
        i = f.readline()

    return n, m, g

def bipartit(graf, src, n):
    culori = [-1] * (n + 1)
    culori[src] = 1
    q = deque()
    q.append(src)
    while q:
        u = q.popleft()

        if graf[u][u] == 1:
            return False
        
        for v in range(n + 1):
            if graf[u][v] != 0 and culori[v] == -1:
                culori[v] = 1 - culori[u]
                q.append(v)
            elif graf[u][v] != 0 and culori[v] == culori[u]:
                return False

    return True, culori

n, m, g = citireGraf()
b, bp = bipartit(g, 1, n)
print(bp)
if b:
    print("Da")
else: print("Nu")

