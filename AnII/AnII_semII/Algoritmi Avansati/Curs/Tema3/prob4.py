import math
import random
import numpy as np

f = open("date.in")
M = []
n = int(f.readline())
i = 0
while i < n:
    p = f.readline()
    M.append([float(p.split()[0]), float(p.split()[1])])
    i += 1

A1 = M[0]
for p in M[1:]:
    if A1 > p:
        A1 = p

valid = True
L = [A1]

while valid:
    curent = L[-1]
    i = random.randint(0, len(M) - 1)
    while i == M.index(curent):
        i = random.randint(0, len(M) - 1)
    piv = M[i]

    for i in range(len(M)):
        if i != M.index(piv) and i != M.index(curent):
            p = M[i]
            det = np.linalg.det(np.array([[1, 1, 1], [curent[0], piv[0], p[0]], [curent[1], piv[1], p[1]]]))
            if det < 0:
                piv = p

    if piv != L[0]:
        L.append(piv)
    else: valid = False

subTur = [x for x in L]
neviz = [x for x in L if x not in subTur]

while len(neviz):
    curent = neviz[0]
    neviz = neviz[1:]
    m1, m2 = -1, -1
    for i in range(len(subTur)):
        j, index = 0, 0
        if i < len(subTur) - 1:
            j = i + 1

        d1 = math.dist(subTur[i], curent)
        d2 = math.dist(curent, subTur[i])
        d3 = math.dist(subTur[i], subTur[j])
        e1 = d1 + d2 - d3
        e2 = (d1 + d2) / d3

        if m1 == -1 or (e1 < m1 and e2 < m2):
            m1, m2, index = e1, e2, j

    subTur.insert(index, curent)

print("TSP:")
for p in subTur:
    if p != subTur[-1]:
        print("(" + str(p[0]) + ", " + str(p[1]) + ")", end=", ")
    else: print("(" + str(p[0]) + ", " + str(p[1]) + ")")