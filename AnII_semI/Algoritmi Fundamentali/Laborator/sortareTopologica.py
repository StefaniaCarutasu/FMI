
f = open("graf.in")
infinit = float('inf')

#LISTA DE MUCHII 
def citireMuchii():
    n = f.readline()
    n = int(n)
    mu = []
    i = f.readline()
    while i:
        x, y= i.split()
        x, y = int(x), int(y)
        mu.append((x, y))
        i = f.readline()
    return n, mu
def topSort(nod, vizitati, stiva, listaMuchii):
    vizitati[nod] = 1
    for i in listaMuchii:
        if i[0] == nod and vizitati[i[1]] == 0:
            topSort(i[1], vizitati, stiva, listaMuchii)
    stiva.append(nod)

def sortareTopologica(listaMuchii):
    vizitati = [0] * (len(listaMuchii) + 1)
    stiva = []
    for i in range(1, len(listaMuchii)):
        if vizitati[i] == 0:
            topSort(i, vizitati, stiva, listaMuchii)
    print(stiva[::-1])

n, muchii = citireMuchii()
sortareTopologica(muchii)