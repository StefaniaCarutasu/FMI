import numpy as np
import random
f = open("date.in")
M = []
n = int(f.readline())
i = 0
#citesc punctele
while i < n:
    p = f.readline()
    M.append([float(p.split()[0]), float(p.split()[1])])
    i += 1

#aleg punctul initial care apartine frontierei (cel mai mic dpdv lexicografic)
A1 = M[0]
for p in M[1:]:
    if A1 > p:
        A1 = p

valid = True
L = [A1]

while valid:
    curent = L[-1]
    i = random.randint(0, len(M) - 1)       #aleg un pivot arbitrar diferit de Ak
    while i == M.index(curent):
        i = random.randint(0, len(M) - 1)
    piv = M[i]

    for i in range(len(M)):
        if i != M.index(piv) and i != M.index(curent):
            p = M[i]
            #verific pozitia punctului curent fata de muchia AkS (S fiind pivotul ales anterior)
            det = np.linalg.det(np.array([[1, 1, 1], [curent[0], piv[0], p[0]], [curent[1], piv[1], p[1]]]))
            if det < 0:
                piv = p
    #verific ca pivotul sa fie diferit de primul punct al frontierei s
    if piv != A1:
        L.append(piv)
    else: valid = False

#afisez frontiera
print("Frontiera: ")
for p in L:
    if p != L[-1]:
        print("(" + str(p[0]) + ", " + str(p[1]) + ")", end = ", ")
    else: print("(" + str(p[0]) + ", " + str(p[1]) + ")")