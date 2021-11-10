f = open("date_p2.in")
def citire():
    n = int(f.readline())
    puncte = []
    for i in range(n):
        puncte.append([float(x) for x in f.readline()])

    Q = [float(x) for x in f.readline().split()]
    f.close()
    return n, Q, puncte


n, Q, puncte = citire()

# determinarea extremitatilor laterale
maxX = max(puncte, key = lambda x: x[0])
minX = min(puncte, key = lambda x: x[0])

# determinarea extremitatilor superioara si superioara
maxY = max(puncte, key = lambda x: x[1])
minY = min(puncte, key = lambda x: x[1])

isX = 1
isY = 1

# pentru x-monotonie parcurg poligonul de la cel mai din dreapta punct la cel mai din stanga
# verific daca se respecta x-monotonia

i = puncte.index(maxX)
while puncte[i] != minX:
    j = 0
    if i < n - 1:
        j = i + 1
    if puncte[j][0] > puncte[i][0]:
        isX = 0
        break
    i = j

if isX:
    # parcug poligonul de la stanga la dreapta
    i = puncte.index(minX)
    while puncte[i] != maxX:
        j = 0
        if i < n - 1:
            j = i + 1
        if puncte[j][0] < puncte[i][0]:
            isX = 0
            break
        i = j
    if isX:
        print("Poligon x-monoton")
    else: print("Nu este x-monoton")
else: print("Nu este x-monoton")

# pentru y-monotonie parcurg poligonul de la extremitatea inferioara la extremitatea superioara
# verific daca se respecta y-monotonia

i = puncte.index(maxY)
while puncte[i] != minY:
    j = 0
    if i < n - 1:
        j = i + 1
    if puncte[j][1] < puncte[i][1]:
        isX = 0
        break
    i = j

if isY:
    # parcurg poligonul de sus in jos
    i = puncte.index(minY)
    while puncte[i] != maxY:
        j = 0
        if i < n - 1:
            j = i + 1
        if puncte[j][1] > puncte[i][1]:
            isX = 0
            break
        i = j
    if isY:
        print("Poligon y-monoton")
    else: print("Nu este y-monoton")
else: print("Nu este y-monoton")