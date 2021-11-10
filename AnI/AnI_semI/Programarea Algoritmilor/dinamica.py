f = open("date.in")
inf = float('inf')
"""
#secventa crescatoare de lungime maxima
def citire():
    l = f.readline().split()
    i = [int(k) for k in l]
    return i
arr = citire()
length = [1 for i in range(len(arr))]
subSequence = [-1 for i in range(len(arr))]
print(arr)
for i in range(1, len(arr)):
    for j in range(i):
        if arr[i] > arr[j]:
            if length[i] <= length[j] + 1:
                length[i] = length[j] + 1
                subSequence[i] = j

print("Cea mai lunga subsecventa are", max(length), "elemente", sep=" ")
i = length.index(max(length))

secv = []
while i != -1:
    secv.append(arr[i])
    i = subSequence[i]
secv.reverse()
print("Secventa crescatoare de lungime maxima este:", *secv)


#divide
#mediana a 2 vectori sortati de dimensiuni diferite

def citire():
    v = f.readline().split()
    v1 = [int(x) for x in v]
    v = f.readline().split()
    v2 = [int(x) for x in v]
    return v1, v2
def mediana(v1, v2):
    if len(v1) <= 2:
        i = 0
        if len(v2) % 2 == 1:
            j = len(v2) // 2
            k = len(v2) // 2
        else:
            j = len(v2) // 2 - 1
            k = len(v2) // 2
        v = []
        while i < 2 and j <= k:
            if v1[i] < v2[j]:
                v.append(v1[i])
                i += 1
            else:
                v.append(v2[j])
                j += 1
        while i < 2:
            v.append(v1[i])
            i += 1
        while j <= k:
            v.append(v2[j])
            j += 1
        if len(v):
            m = v[len(v) // 2]
        else:
            m = (v[len(v) // 2] + v[len(v) // 2 - 1]) / 2
        return m
    elif len(v2) <= 2:
        j = 0
        if len(v1) % 2 == 1:
            i = len(v1) // 2
            k = len(v1) // 2
        else:
            i = len(v1) // 2 - 1
            k = len(v1) // 2
        v = []
        while j < 2 and i <= k:
            if v2[j] < v1[i]:
                v.append(v2[j])
                j += 1
            else:
                v.append(v1[i])
                i += 1
        while j < 2:
            v.append(v2[j])
            j += 1
        while i <= k:
            v.append(v1[i])
            i += 1
        if len(v):
            m = v[len(v) // 2]
        else:
            m = (v[len(v) // 2] + v[len(v) // 2 - 1]) / 2
        return m
    else:
        if len(v1) % 2 == 1:
            m1 = v1[len(v1) // 2]
        else:
            m1 = (v1[len(v1) // 2] + v1[len(v1) // 2 - 1]) / 2
        if len(v2) % 2 == 1:
            m2 = v2[len(v2) // 2]
        else:
            m2 = (v2[len(v1) // 2] + v2[len(v2) // 2 - 1]) / 2
        if m2 < m1:
            return mediana(v1[:(len(v1) // 2)], v2[(len(v2) // 2):])
        else:
            return mediana(v1[(len(v1) // 2):], v2[:(len(v2) // 2)])


v1, v2 = citire()
print(mediana(v1, v2))


#longest common subsequence
def citire():
    s1 = list(f.readline())
    s1.pop()
    s2 = list(f.readline())
    return s1, s2

s1, s2 = citire()
matrice = [[0 for j in range(len(s1) + 1) ] for i in range(len(s2) + 1)]
print(s1, s2, sep='\n')
for i in range(1,len(s2) + 1):
    for j in range(1,len(s1) + 1):
        if s1[j - 1] == s2[i - 1]:
            matrice[i][j] = matrice[i - 1][j - 1] + 1
        else:
            matrice[i][j] = max(matrice[i - 1][j], matrice[i][j - 1])
for linie in matrice:
    print(*linie)
sir = ""
i = len(matrice) - 1
j = len(matrice[0]) - 1
k = 0
m = max([max(*linie) for linie in matrice])
while k < m:
    if s1[j - 1] == s2[i - 1] and matrice[i][j] >= max(matrice[i - 1]):
        sir += s1[j - 1]
        j -= 1
        i -= 1
        k += 1
    else:
        if j > 0:
            j -= 1
        else:
            j = len(matrice[0]) - 1
            i -= 1
print(sir)


def citire():
    a = f.readline().split()
    arr = [int(x) for x in a]
    return arr

arr = citire()
minJump = [inf for i in arr]
minJump[0] = 0
jumpPath = [-1 for i in arr]

for i in range(1, len(arr)):
    for j in range(len(arr)):
        if i <= j + arr[j]:
            minJump[i] = min(minJump[i], minJump[j] + 1)
            jumpPath[i] = j


#monede
def citire():
    suma = int(f.readline())
    c = f.readline().split()
    monede = [int(x) for x in c]
    return monede, suma

monede, suma = citire()
matrice = [[0 for i in range(suma + 1)] for j in range(len(monede) + 1)]

matrice[0][0] = 1
for i in range(1, suma + 1):
    for j in range(len(monede) + 1):
        if monede[i - 1] > j:
            matrice[i][j] = matrice[i - 1][j]
        else:
            matrice[i][j] = matrice[i - 1][j] + matrice[i][j - i]

for linie in matrice:
    print(*linie)

print("Suma", suma, "se poate obtine in", matrice[suma][len(monede)], "moduri")


#distanta Levenshtein
def citire():
    str1 = list(f.readline())
    str1.pop()
    str2 = list(f.readline())
    return str1, str2

s1, s2 = citire()
matrice = [[0 for i in range(len(s1) + 1)] for j in range(len(s2) + 1)]
for i in range(1, len(s1) + 1):
    matrice[0][i] = i
for i in range(1, len(s2) + 1):
    matrice[i][0] = i
for i in range(1, len(s1) + 1):
    for j in range(1, len(s2) + 1):
        if s1[i - 1] != s2[j - 1]:
            matrice[i][j] = min(matrice[i][j - 1], matrice[i - 1][j], matrice[i - 1][j - 1]) + 1
        else:
            matrice[i][j] = matrice[i - 1][j - 1]
print(s1, s2)

for linie in matrice:
    print(*linie)

print("Distanta Levenshtein:", matrice[len(s2)][len(s1)])


#rucsac
def citire():
    G = int(f.readline())
    obiecte = []
    i = f.readline()
    while i:
        w, v = i.split()
        w, v = int(w), int(v)
        obiecte.append([w,v])
        i = f.readline()
    return obiecte, G

obiecte, greutate = citire()
print(obiecte)
matrice = [[0 for i in range(greutate + 1)] for j in range(len(obiecte) + 1)]
for i in range(greutate + 1):
    matrice[0][i] = i
for i in range(1, len(obiecte) + 1):
    for j in range(greutate + 1):
        if obiecte[i - 1][0] <= j:
            matrice[i][j] = max(obiecte[i - 1][1], matrice[i - 1][j])
        else:
            matrice[i][j] = matrice[i - 1][j]
for i in matrice:
    print(*i)


#0/1 Knapsack
def citire():
    K = int(f.readline()) 
    S = []
    i = f.readline()
    while i:
        s = int(i)
        S.append(s)
        i = f.readline()
    return K, S, len(S)

K, S, n = citire()
matrice = [[0 for i in range (K + 1)] for j in range(n + 1)]

for i in range(1, n + 1):
    for j in range(1, K + 1):
        if j - S[i - 1] >= 0:
            matrice[i][j] = max(matrice[i - 1][j], S[i - 1]) + matrice[i - 1][g - S[i - 1]]
        else:
            matrice[i][j] = matrice[i - 1][j]

print("Valoarea totala este: ", matrice[n][K])

#afisare 
i = n
j = K
while i > 0:
    if matrice[i - 1][j] == matrice[i][j]:
        i -= 1
    else:
        print(i, end = " ")
        j -= S[i - 1]
        i -= 1


#0/1 Knapsack pe steroizi

#citire date
G = int(f.readline())   #greutatea totala
i = f.readline()    #obiectul curent
maximum = float(i.split()[0]) / float(i.split()[1])    #maximul
i = f.readline()
while i:
    if G >= int(i.split()[1]) and float(i.split()[0]) / float(i.split()[1]) >= maximum:
        G -= int(i.split()[1])
        maximum = float(i.split()[0]) / float(i.split()[1])
        print(i.split())
    elif float(i.split()[0]) / float(i.split()[1]) >= maximum and G < int(i.split()[1]):
        maximum = float(i.split()[0]) / float(i.split()[1])
    i = f.readline()


#0/1 Knapsack pe steroizi

G = int(f.readline())   #greutatea totala
g = int(f.readline())   #greutatea obiectului
maxim = 0
while g:
    if G >= g and maxim <= g:
        G -= g
        maxim = g
        print(g)
    g = f.readline()


#0/1 Knapsack pe steroizi
#la fiecare pas verific 2 obiecte si iau maximul dintre cele 2 si doamne ajuta

G = int(f.readline())   #greutatea totala
g1 = int(f.readline())   #greutatea obiectului 1
g2 = int(f.readline())   #greutatea obiectului 2

while (g1 or g2) and G > 0:
    if g1 and g2 is None:
        if G >= g1:
            print(g1)
            G -= g1
            g1 = f.readline()
    elif g2 and g1 is None:
        if G >= g2:
            print(g2)
            G -= g2
            g2 = f.readline()
    else:
        if g2 > g1 and G >= g2:
            G -= g2
            print(g2)
            g2 = f.readline()
            if g2:
                g2 = int(g2)
        elif g2 < g1 and G >= g1:
            G -= g1
            print(g1)
            g1 = f.readline()
            if g1:
                g1= int(g1)
        else:
            g1 = f.readline()
            if g1:
                g1 = int(g1)
            g2 = f.readline()
            if g2:
                g2 = int(g2)

f.close()
f = open("date.in")
g1 = int(f.readline())
print("Suma totala:", g1 - G)
"""