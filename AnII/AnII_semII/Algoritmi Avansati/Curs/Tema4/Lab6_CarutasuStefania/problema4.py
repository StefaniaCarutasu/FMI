#AC sau BD ilegala
import numpy as np
f = open("date_p2.in")
def citire():
    i = f.readline().split()
    puncte = []
    while i:
        puncte.append([float(i[0]), float(i[1])])
        i = f.readline().split()
    return puncte

def detTeta(p1, p2, p3, p4):
    teta_matrix = np.array([[p1[0], p1[1], p1[0] ** 2 + p1[1] ** 2, 1], [p2[0], p2[1], p2[0] ** 2 + p2[1] ** 2, 1],
                                [p3[0], p3[1], p3[0] ** 2 + p3[1] ** 2, 1], [p4[0], p4[1], p4[0] ** 2 + p4[1] ** 2, 1]])
    teta = np.linalg.det(teta_matrix)

    return teta

puncte = citire()
A, B, C, D = puncte[0], puncte[1], puncte[2], puncte[3]

tetaABCD = detTeta(A, B, C, D)
tetaACBD = detTeta(A, C, B, D)

if tetaABCD > 0:
    print("AC este ilegala")
elif tetaACBD > 0:
    print("BD este ilegala")
else: print("Nu avem muchii ilegale")




