from collections import deque
f = open("graf.in")
def citireGraf():
    n, m = f.readline().split()
    n, m = int(n), int(m)
    d = {}
    i = f.readline()
    while i:
        x, y = i.split()
        x, y = int(x), int(y)
        if x in d.keys():
            d[x].append(y)
        else: d[x] = [y]
        if y in d.keys():
            d[y].append(x)
        else: d[y] = [x]
        i = f.readline()
    return n, m, d

def canPaint(graf, n, m, culori):
    vizitati = [0] * (n + 1)
    maxColors = 1
    for sv in range (1, n + 1):
        if vizitati[sv] == 1: 
            continue
        vizitati[sv] = 1
        coada = deque()
        coada.append(sv)

        while coada:
            top = coada.popleft()
            for i in graf[top]:
                if culori[top] == culori[i] :
                    culori[i] += 1

                maxColors = max(maxColors, max(culori[top], culori[i]))

                if maxColors > m:
                    return 0, culori

                if vizitati[i] == 0:
                    vizitati[i] = 1
                    coada.append(i)
    
    return 1, culori

n, m, graf = citireGraf()
culori = [1] * (n + 1) 
b, culori = canPaint(graf, n, 7, culori)
if b:
    print("Graful este 6 colorabil :)")
    for i in range(1, n + 1):
        print(i, "->", culori[i])     
else: print("Graful nu este 6 colorabil :(")   
