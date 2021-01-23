f = open("graf.in")

#MATRICE ADIACENTA GRAFURI NEORIENTATE
def citireMatr():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    a = [[]] * (n + 1)
    for i in range(n + 1):
        a[i] = [0] * (n + 1)
    i = f.readline()
    while i:
        x, y = i.split()
        x, y = int(x), int(y)
        a[x][y] = a[y][x] = 1
        i = f.readline()
    return n, m, a

#LISTA DE ADIACENTA GRAFURI NEORIENTATE
def citireList():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    d = {}
    i = f.readline()
    while i:
        x, y = i.split()
        x, y = int(x), int(y)
        if x in d:
            d[x].append(y)
        else:
            d[x] = [y]
        if y in d:
            d[y].append(x)
        else:
            d[y] = [x]
        i = f.readline()
    return n, m, d

#MATRICE DE ADIACENTA GRAFURI ORIENTATE
def citireMatrOr():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    a = [[]] * (n + 1)
    for i in range(n + 1):
        a[i] = [0] * (n + 1)
    i = f.readline()
    while i:
        x, y = i.split()
        x, y = int(x), int(y)
        a[x][y] = 1
        i = f.readline()
    return n, m, a

#LISTA DE ADIACENTA GRAFURI ORIENTATE
def citireListOr():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    d = {}
    i = f.readline()
    while i:
        x, y = i.split()
        x, y = int(x), int(y)
        if x in d:
            d[x].append(y)
        else:
            d[x] = [y]
        i = f.readline()
    return n, m, d

#MATRICE ADIACENTA => LISTA ADIACENTA
def matrAdToListAd(n, a):
    d = {}
    for i in range(n):
        d[i + 1] = []
        for j in range(n):
            if a[i][j] == 1:
                d[i + 1].append(j + 1)
    return d

#LISTA ADIACENTA => MATRICE ADIACENTA
def listAdToMatrAd(n, d):
    a = [[]] * (n + 1)
    for i in range(n + 1):
        a[i] = [0] * (n + 1)
    for i in d:
        for j in d[i]:
            a[i][j] = 1
    return a

#MATRICE ADIACENTA GRAFURI NEORIENTATE PONDERATE
def citireMatrPond():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    a = [[]] * (n + 1)
    for i in range(n + 1):
        a[i] = [0] * (n + 1)
    i = f.readline()
    while i:
        x, y, z = i.split()
        x, y, z = int(x), int(y), int(z)
        a[x][y] = a[y][x] = z
        i = f.readline()
    return n, m, a

#LISTA DE ADIACENTA GRAFURI NEORIENTATE PONDERATE
def citireListPond():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    d = {}
    i = f.readline()
    while i:
        x, y, z = i.split()
        x, y, z = int(x), int(y), int(z)
        if x in d:
            d[x].append((y, z))
        else:
            d[x] = [(y, z)]
        if y in d:
            d[y].append((x, z))
        else:
            d[y] = [(x, z)]
        i = f.readline()
    return n, m, d

#MATRICE DE ADIACENTA GRAFURI ORIENTATE PONDERATE
def citireMatrOrPond():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    a = [[]] * (n + 1)
    for i in range(n + 1):
        a[i] = [0] * (n + 1)
    i = f.readline()
    while i:
        x, y, z = i.split()
        x, y, z = int(x), int(y), int(z)
        a[x][y] = z
        i = f.readline()
    return n, m, a

#LISTA DE ADIACENTA GRAFURI ORIENTATE PONDERATE
def citireListOrPond():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    d = {}
    i = f.readline()
    while i:
        x, y, z = i.split()
        x, y, z = int(x), int(y), int(z)
        if x in d:
            d[x].append((y, z))
        else:
            d[x] = [(y, z)]
        i = f.readline()
    return n, m, d

#LISTA DE MUCHII
def citireMuchii():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    mu = []
    i = f.readline()
    while i:
        x, y = i.split()
        x, y = int(x), int(y)
        mu.append((x, y))
        i = f.readline()
    return n, m, mu

#LISTA DE MUCHII PONDERATE
def citireMuchiiPond():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    mu = []
    i = f.readline()
    while i:
        x, y, z = i.split()
        x, y, z = int(x), int(y), int(z)
        mu.append((x, y, z))
        i = f.readline()
    return n, m, mu