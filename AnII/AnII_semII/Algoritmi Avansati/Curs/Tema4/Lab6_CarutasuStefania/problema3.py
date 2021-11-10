#fata de varianta trimisa la laborator am schimbat coordonatele punctelor din
#int in float si am scris intr-o functie calcularea valorii lui teta

#pozitia unui punct fata de cercul circumscris

import numpy as np
f = open("date_p2.in")
def citire():
    i = f.readline().split()
    puncte = []
    while i:
        puncte.append([float(i[0]), float(i[1])])
        i = f.readline().split()
    return puncte

puncte = citire()
A, B, C, D = puncte[0], puncte[1],puncte[2], puncte[3]

def detTeta(p1, p2, p3, p4):
    teta_matrix = np.array([[p1[0], p1[1], p1[0] ** 2 + p1[1] ** 2, 1], [p2[0], p2[1], p2[0] ** 2 + p2[1] ** 2, 1],
                                [p3[0], p3[1], p3[0] ** 2 + p3[1] ** 2, 1], [p4[0], p4[1], p4[0] ** 2 + p4[1] ** 2, 1]])
    teta = np.linalg.det(teta_matrix)

    return teta

#in functie de valoarea lui teta
#teta = 0 atunci punctul este pe cerc
#teta > 0 atunci punctul este in interior
#teta < 0 atunci punctul este in exterior
teta = detTeta(A, B, C, D)

if teta == 0:
    print("D este pe cerc")
elif teta > 0:
    print("D este in interior")
else: print("D este in exterior")
