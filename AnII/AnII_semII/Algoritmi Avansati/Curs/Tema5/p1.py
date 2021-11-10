#modificari fata de varianta trimisa in timpul laboratorului:
#initial citeam coordonatele din fisier si le converteam la int in loc de float
#pastram in memorie dreptele si dupa nu le mai utilizam si am renuntat la acest lucru

f = open("date_p1.in")
infinity = float('inf')
negativeInfinity = float('-inf')

n = int(f.readline())

xmax = ymax = negativeInfinity
xmin = ymin = infinity

for i in range(n):
    a, b, c = [float(x) for x in f.readline().split()]
    #am citit dreptele si calculez pentru fiecare in parte valoarea pentru care are loc inegalitatea
    if a == 0:
        v = -c / b
        if b < 0:
            if v > ymax:
                ymax = v
        else:
            if v < ymin:
                ymin = v
    else:
        v = -c / a
        if a < 0:
            if v > xmax:
                xmax = v
        else:
            if v < xmin:
                xmin = v

if xmin > xmax and ymin > ymax:
    if (xmin == infinity or ymin == infinity) or (ymax == negativeInfinity or xmax == negativeInfinity):
        print("Intersectia nevida si nemarginita")
    else:
        print("Intersectie nevida si margitita")
else:
    print("Intersectie vida")





