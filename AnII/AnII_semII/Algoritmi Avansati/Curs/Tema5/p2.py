f = open("date_p2.in")
infinity = float('inf')
negativeInfinity = float('-inf')

Q = [float(x) for x in f.readline().split()]

n = int(f.readline())

xmin = negativeInfinity
xmax = infinity
ymin = negativeInfinity
ymax = infinity

for i in range(n):
    a, b, c = [float(x) for x in f.readline().split()]
    #pentru fiecare semiplan in parte calculez valoarea lui x respectiv y
    #compar aceasta valoarea cu coordonatele punctului
    #apoi compar cu cele 4 coordonate definite anterior ce reprezita coordonatele dreptunghiului

    if a == 0:
        v = -c / b
        if v > Q[0]:
            if v < xmax:
                xmax = v
        elif v == Q[0]:
            if abs(xmin - v) < abs(xmax - v):
                xmax = v
            else:
                xmin = v
        else:
            if v > xmin:
                xmin = v
    else:
        v = -c / a
        if v > Q[1]:
            if v < ymax:
                ymax = v
        elif v == Q[1]:
            if abs(ymin - v) <= abs(ymax - v):
                ymax = v
            else:
                ymin = v
        else:
            if v > ymin:
                ymin = v



if xmax == infinity or ymax == infinity or ymin == negativeInfinity or xmin == negativeInfinity:
    print("(a) Nu exista dreptunghi cu prorpietatea ceruta")
else:
    print("(a) Exista un dreptunghi cu proprietatea ceruta")
    A = (ymax - ymin) * (xmax - xmin)
    print("(b) Valoarea minima a ariilor dreptunghiurilor cu proprietatea ceruta este ", A)

