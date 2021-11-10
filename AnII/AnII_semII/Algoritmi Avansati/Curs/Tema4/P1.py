import numpy as np
import shapely.geometry as sh

f = open("date.in")
def citire():
    n = int(f.readline())
    puncte = []
    for i in range(n):
        puncte.append([float(x) for x in f.readline()])

    Q = [float(x) for x in f.readline().split()]
    f.close()
    return n, Q, puncte

n, Q, puncte = citire()

#extremitatile poligonului
maxX = max(puncte, key = lambda x: x[0])[0]
minX = min(puncte, key = lambda x: x[0])[0]
maxY = max(puncte, key = lambda x: x[1])[1]
minY = min(puncte, key = lambda x: x[1])[1]

# verific daca se afla intre extremitatile poligonului
# daca nu este atunci cu siguranta nu va fi in interiorul poligonului
if minX <= Q[0] <= maxX and minY <= Q[1] <= maxY:
    # verific daca punctul se afla pe una dintre laturi
    ok = 0
    i = 0
    for j in range(n):
        if i < n - 1:
            index = i + 1
        else: index = 0

        minimX = min(puncte[i][0], puncte[index][0])
        maximX = max(puncte[i][0], puncte[index][0])
        minimY = min(puncte[i][1], puncte[index][1])
        maximY = max(puncte[i][1], puncte[index][1])

        if minimX <= Q[0] <= maximX and minimY <= Q[1] <= maximY:
            x1, y1 = puncte[i][0], puncte[i][1]
            x2, y2 = puncte[index][0], puncte[index][1]
            x3, y3 = Q[0], Q[1]

            determinant = np.array([[1, 1, 1], [x1, x2, x3], [y1, y2, y3]])
            viraj = np.linalg.det(determinant)

            if viraj == 0:
                print("Punctul este pe una dintre laturi")
                ok = True
                break
        i = index

    if not ok:
        # determin semidreapta care trece prin punctul Q si este paralela cu Ox
        pSemidr = [maxX + 1, Q[1]]
        l1 = sh.LineString([Q, pSemidr])

        # determin cu cate laturi se intersecteaza semidreapta determinata anterior
        intersectii = 0
        i = 0
        for j in range(n):
            if i < n - 1:
                index = i + 1
            else: index = 0

            l2 = sh.LineString([puncte[i], puncte[index]])
            pctIntersectie = l1.intersection(l2)

            if pctIntersectie:
                x1, y1 = puncte[i][0], puncte[i][1]
                x2, y2 = puncte[index][0], puncte[index][1]
                x3, y3 = pctIntersectie.x, pctIntersectie.y

                determinant = np.array([[1, 1, 1], [x1, x2, x3], [y1, y2, y3]])
                viraj = np.linalg.det(determinant)

                if viraj == 0:
                    if(x1 == x3 and y1 == y3 and y1 < y2) or (x2 == x3 and y2 == y3 and y2 < y1):
                        continue
                    else: intersectii += 1

            i = index

        if intersectii % 2:
            print("Punctul se afla in interior")
        else:
            print("Punctul se afla in exterior")
else: print("Punctul se afla in exterior")







